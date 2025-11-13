from ctypes import BigEndianStructure, c_char, c_uint8, c_uint16, c_uint32, sizeof, memmove, addressof
import struct
import os

class BOMHeader(BigEndianStructure):
    _pack_ = 1
    _fields_ = [("magic", c_char*8),
                ("version", c_uint32),
                ("numberOfBlocks", c_uint32),
                ("indexOffset", c_uint32),
                ("indexLength", c_uint32),
                ("varsOffset", c_uint32),
                ("varsLength", c_uint32)]

class BOMPointer(BigEndianStructure):
    _pack_ = 1
    _fields_ = [("address", c_uint32),
                ("length", c_uint32)]

class BOMBlockTable(BigEndianStructure):
    _pack_ = 1
    _fields_ = [("numberOfBlockTablePointers", c_uint32)]

class BOMVars(BigEndianStructure):
    _pack_ = 1
    _fields_ = [("count", c_uint32)]

class BOMVar(BigEndianStructure):
    _pack_ = 1
    _fields_ = [("index", c_uint32),
                ("length", c_uint8)]

class BOMTree(BigEndianStructure):
    _pack_ = 1
    _fields_ = [("tree", c_char*4),
                ("version", c_uint32),
                ("child", c_uint32),
                ("blockSize", c_uint32),
                ("pathCount", c_uint32),
                ("unknown3", c_uint8)]

class BOMPaths(BigEndianStructure):
    _pack_ = 1
    _fields_ = [("isLeaf", c_uint16),
                ("count", c_uint16),
                ("forward", c_uint32),
                ("backward", c_uint32)]

class BOMPathIndices(BigEndianStructure):
    _pack_ = 1
    _fields_ = [("index0", c_uint32),
                ("index1", c_uint32)]

def structRead(f_in, classType):
    tmp = classType()
    sz = sizeof(tmp)
    bytes_data = f_in.read(sz)
    if len(bytes_data) < sz:
        return None
    memmove(addressof(tmp), bytes_data, sz)
    return tmp

def parse_tree_node(f, pointers, node_id, depth=0):
    """Recursively parse tree nodes"""
    if node_id >= len(pointers):
        return []

    ptr = pointers[node_id]
    if ptr.address == 0:
        return []

    results = []

    try:
        f.seek(ptr.address)
        paths = structRead(f, BOMPaths)

        if paths is None:
            return []

        for i in range(paths.count):
            indices = structRead(f, BOMPathIndices)
            if indices:
                results.append({
                    'key_index': indices.index0,
                    'value_index': indices.index1,
                    'depth': depth
                })

        # Recursively process child nodes if not a leaf
        if paths.isLeaf == 0 and paths.count > 0:
            # Get first index and recurse
            f.seek(ptr.address + sizeof(BOMPaths))
            first_indices = structRead(f, BOMPathIndices)
            if first_indices:
                results.extend(parse_tree_node(f, pointers, first_indices.index0, depth + 1))

        # Process forward pointer
        if paths.forward != 0:
            results.extend(parse_tree_node(f, pointers, paths.forward, depth))

    except Exception as e:
        pass

    return results

def extract_renditions(filename, output_dir):
    """Extract renditions (actual images) from Assets.car"""

    os.makedirs(output_dir, exist_ok=True)

    with open(filename, 'rb') as f:
        # Read header
        header = structRead(f, BOMHeader)

        print("="*60)
        print("Advanced Assets.car Parser - Rendition Extractor")
        print("="*60)
        print(f"Magic: {header.magic}")
        print(f"Version: {header.version}")
        print(f"Number of blocks: {header.numberOfBlocks}\n")

        # Read block table
        f.seek(header.indexOffset)
        table = structRead(f, BOMBlockTable)

        pointers = []
        for i in range(table.numberOfBlockTablePointers):
            p = structRead(f, BOMPointer)
            pointers.append(p)

        # Read variables
        f.seek(header.varsOffset)
        variables = structRead(f, BOMVars)

        vars_dict = {}
        for i in range(variables.count):
            v = structRead(f, BOMVar)
            name_bytes = f.read(v.length)
            name = name_bytes.decode('utf-8', errors='ignore')
            vars_dict[name] = v.index

        print("Variables found:", ", ".join(vars_dict.keys()))
        print()

        # Parse RENDITIONS tree
        if 'RENDITIONS' in vars_dict:
            renditions_block_id = vars_dict['RENDITIONS']
            ptr = pointers[renditions_block_id]

            print(f"Parsing RENDITIONS tree (block {renditions_block_id})...")

            f.seek(ptr.address)
            tree = structRead(f, BOMTree)

            if tree and tree.tree == b'tree':
                print(f"  Tree version: {tree.version}")
                print(f"  Path count: {tree.pathCount}")
                print(f"  Child node: {tree.child}")
                print()

                # Parse the tree structure
                entries = parse_tree_node(f, pointers, tree.child)

                print(f"Found {len(entries)} tree entries")
                print()

                # Extract renditions
                extracted = 0

                for idx, entry in enumerate(entries):
                    value_idx = entry['value_index']

                    if value_idx < len(pointers):
                        val_ptr = pointers[value_idx]

                        if val_ptr.address != 0 and val_ptr.length > 100:
                            f.seek(val_ptr.address)
                            data = f.read(val_ptr.length)

                            # Look for rendition header (CSI header)
                            # Renditions typically start with specific magic bytes
                            if len(data) > 184:  # CSI header is 184 bytes
                                # Check for image data after header
                                has_image = False
                                img_type = "unknown"
                                img_offset = 0

                                # Search for image signatures in the data
                                png_sig = b'\x89PNG\r\n\x1a\n'
                                jpeg_sig = b'\xff\xd8\xff'
                                bmp_sig = b'BM'

                                if png_sig in data:
                                    has_image = True
                                    img_type = "png"
                                    img_offset = data.find(png_sig)
                                elif jpeg_sig in data:
                                    has_image = True
                                    img_type = "jpg"
                                    img_offset = data.find(jpeg_sig)
                                elif data[:2] == bmp_sig:
                                    has_image = True
                                    img_type = "bmp"
                                    img_offset = 0

                                if has_image:
                                    # Extract just the image data
                                    if img_type == "png":
                                        end_marker = b'IEND\xae\x42\x60\x82'
                                        end_pos = data.find(end_marker, img_offset)
                                        if end_pos != -1:
                                            image_data = data[img_offset:end_pos + 8]
                                        else:
                                            image_data = data[img_offset:]
                                    elif img_type == "jpg":
                                        end_marker = b'\xff\xd9'
                                        end_pos = data.find(end_marker, img_offset + 3)
                                        if end_pos != -1:
                                            image_data = data[img_offset:end_pos + 2]
                                        else:
                                            image_data = data[img_offset:]
                                    else:
                                        image_data = data[img_offset:]

                                    filename_out = f"rendition_{extracted:03d}.{img_type}"
                                    output_path = os.path.join(output_dir, filename_out)

                                    with open(output_path, 'wb') as out:
                                        out.write(image_data)

                                    print(f"  [{img_type.upper()}] Extracted: {filename_out} ({len(image_data)} bytes)")
                                    extracted += 1

                print(f"\n{'='*60}")
                print(f"Total renditions extracted: {extracted}")
                print(f"Output directory: {output_dir}")
                print(f"{'='*60}")

        else:
            print("RENDITIONS tree not found in Assets.car")

if __name__ == "__main__":
    car_file = r"D:\Downloads\qora-core-master-final\app\theme\qorai\mac\Assets.car"
    output_dir = r"D:\Downloads\qora-core-master-final\extracted_renditions"

    if not os.path.exists(car_file):
        print(f"Error: File not found: {car_file}")
        exit(1)

    extract_renditions(car_file, output_dir)
