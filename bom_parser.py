from ctypes import BigEndianStructure, c_char, c_uint8, c_uint16, c_uint32, sizeof, memmove, addressof
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

def structRead(f_in, classType):
    tmp = classType()
    sz = sizeof(tmp)
    bytes_data = f_in.read(sz)
    memmove(addressof(tmp), bytes_data, sz)
    return tmp

def extract_assets_from_car(filename, output_dir):
    """Extract assets from Assets.car file"""

    os.makedirs(output_dir, exist_ok=True)

    with open(filename, 'rb') as f:
        # Read header
        header = structRead(f, BOMHeader)

        print("="*60)
        print("BOM Header Information")
        print("="*60)
        print(f"Magic: {header.magic}")
        print(f"Version: {header.version}")
        print(f"Number of blocks: {header.numberOfBlocks}")
        print(f"Index offset: {header.indexOffset}")
        print(f"Index length: {header.indexLength}")
        print(f"Vars offset: {header.varsOffset}")
        print(f"Vars length: {header.varsLength}")

        # Read block table
        f.seek(header.indexOffset)
        table = structRead(f, BOMBlockTable)

        print(f"\nBlock table pointers: {table.numberOfBlockTablePointers}")

        # Read all block pointers
        pointers = []
        for i in range(table.numberOfBlockTablePointers):
            p = structRead(f, BOMPointer)
            pointers.append(p)

        # Read variables
        f.seek(header.varsOffset)
        variables = structRead(f, BOMVars)

        print(f"\nNumber of variables: {variables.count}\n")

        vars_list = []
        for i in range(variables.count):
            v = structRead(f, BOMVar)
            name_bytes = f.read(v.length)
            name = name_bytes.decode('utf-8', errors='ignore')
            vars_list.append((name, v.index))
            print(f"Variable {i}: '{name}' -> Block {v.index}")

        print(f"\n{'='*60}")
        print("Extracting Data Blocks")
        print(f"{'='*60}\n")

        # Extract interesting blocks
        extracted_count = 0

        for name, index in vars_list:
            if index < len(pointers):
                ptr = pointers[index]

                if ptr.address != 0 and ptr.length > 0:
                    f.seek(ptr.address)
                    data = f.read(ptr.length)

                    # Check for image signatures
                    has_image = False
                    img_type = ""

                    if b'\x89PNG' in data:
                        has_image = True
                        img_type = "PNG"
                    elif b'\xff\xd8\xff' in data:
                        has_image = True
                        img_type = "JPEG"
                    elif data[:2] == b'BM':
                        has_image = True
                        img_type = "BMP"
                    elif b'<svg' in data:
                        has_image = True
                        img_type = "SVG"

                    # Save the block
                    safe_name = "".join(c if c.isalnum() or c in "._- " else "_" for c in name)
                    filename_out = f"{safe_name}_block_{index}.dat"

                    if has_image:
                        filename_out = f"{safe_name}_block_{index}_{img_type}.dat"
                        print(f"[{img_type}] Extracting: {name} -> {filename_out} ({ptr.length} bytes)")
                    else:
                        print(f"Extracting: {name} -> {filename_out} ({ptr.length} bytes)")

                    output_path = os.path.join(output_dir, filename_out)
                    with open(output_path, 'wb') as out:
                        out.write(data)

                    extracted_count += 1

        # Also extract large unnamed blocks that might contain images
        print(f"\n{'='*60}")
        print("Extracting Additional Large Blocks")
        print(f"{'='*60}\n")

        for i, ptr in enumerate(pointers):
            if ptr.address != 0 and ptr.length > 5000:  # At least 5KB
                # Check if this block was already extracted
                already_extracted = any(v[1] == i for v in vars_list)

                if not already_extracted:
                    f.seek(ptr.address)
                    data = f.read(ptr.length)

                    # Check for image signatures
                    has_image = False
                    img_type = ""

                    if b'\x89PNG' in data:
                        has_image = True
                        img_type = "PNG"
                    elif b'\xff\xd8\xff' in data:
                        has_image = True
                        img_type = "JPEG"
                    elif data[:2] == b'BM':
                        has_image = True
                        img_type = "BMP"
                    elif b'<svg' in data:
                        has_image = True
                        img_type = "SVG"

                    if has_image:
                        filename_out = f"unnamed_block_{i}_{img_type}.dat"
                        print(f"[{img_type}] Extracting unnamed block {i} -> {filename_out} ({ptr.length} bytes)")

                        output_path = os.path.join(output_dir, filename_out)
                        with open(output_path, 'wb') as out:
                            out.write(data)

                        extracted_count += 1

        print(f"\n{'='*60}")
        print(f"Total files extracted: {extracted_count}")
        print(f"Output directory: {output_dir}")
        print(f"{'='*60}")

if __name__ == "__main__":
    car_file = r"D:\Downloads\qora-core-master-final\app\theme\qorai\mac\Assets.car"
    output_dir = r"D:\Downloads\qora-core-master-final\extracted_car_assets"

    if not os.path.exists(car_file):
        print(f"Error: File not found: {car_file}")
        exit(1)

    extract_assets_from_car(car_file, output_dir)
