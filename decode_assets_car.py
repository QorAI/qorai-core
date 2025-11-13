import struct
import sys
import os

def read_bom_header(file_path):
    """Read and parse the BOM (Bill of Materials) header from Assets.car"""
    with open(file_path, 'rb') as f:
        # Read first 512 bytes to analyze header
        header_data = f.read(512)
        print(f"First 64 bytes (hex): {header_data[:64].hex()}")
        print(f"First 64 bytes (ascii): {header_data[:64]}")

        # Reset to beginning
        f.seek(0)

        # Read BOM magic number - expecting "BOMStore" but could have version byte
        magic = f.read(8)
        print(f"\nMagic bytes: {magic}")
        print(f"Magic hex: {magic.hex()}")

        # Check various BOM signatures
        if b'BOM' not in magic:
            print("Warning: BOM signature not found in expected location")
            print("Continuing with analysis...\n")
        else:
            print("BOM signature found!\n")

        # Try to parse as big-endian
        f.seek(8)
        try:
            # Read version info
            version = struct.unpack('>I', f.read(4))[0]
            print(f"Version (big-endian): {version}")

            # Read number of blocks
            num_blocks = struct.unpack('>I', f.read(4))[0]
            print(f"Number of blocks: {num_blocks}")

            # Read index offset
            index_offset = struct.unpack('>I', f.read(4))[0]
            print(f"Index offset: {index_offset}")

            # Read index length
            index_length = struct.unpack('>I', f.read(4))[0]
            print(f"Index length: {index_length}")

            # Read vars offset
            vars_offset = struct.unpack('>I', f.read(4))[0]
            print(f"Vars offset: {vars_offset}")
        except:
            print("Could not parse header in standard BOM format")

        print(f"\n--- File size: {os.path.getsize(file_path)} bytes ---\n")

        return True

def search_for_strings(file_path, min_length=4):
    """Search for readable strings in the file"""
    print("\n=== Searching for readable strings ===\n")

    with open(file_path, 'rb') as f:
        data = f.read()

    strings = []
    current_string = []

    for byte in data:
        if 32 <= byte <= 126:  # Printable ASCII
            current_string.append(chr(byte))
        else:
            if len(current_string) >= min_length:
                string = ''.join(current_string)
                if string not in strings:
                    strings.append(string)
            current_string = []

    # Print unique strings
    print(f"Found {len(strings)} unique strings (min length {min_length}):\n")
    for s in sorted(strings, key=len, reverse=True)[:50]:  # Show top 50 longest
        print(f"  {s}")

    return strings

def search_for_image_signatures(file_path):
    """Search for common image format signatures"""
    print("\n=== Searching for image signatures ===\n")

    with open(file_path, 'rb') as f:
        data = f.read()

    # Common image signatures
    signatures = {
        b'\x89PNG\r\n\x1a\n': 'PNG',
        b'\xff\xd8\xff': 'JPEG',
        b'GIF87a': 'GIF87a',
        b'GIF89a': 'GIF89a',
        b'%PDF': 'PDF',
        b'RIFF': 'RIFF/WebP',
        b'\x00\x00\x01\x00': 'ICO',
        b'BM': 'BMP',
    }

    found = {}
    for sig, name in signatures.items():
        count = data.count(sig)
        if count > 0:
            found[name] = count
            print(f"  Found {count} {name} signature(s)")

            # Find offsets
            offsets = []
            start = 0
            while True:
                pos = data.find(sig, start)
                if pos == -1:
                    break
                offsets.append(pos)
                start = pos + 1

            print(f"    Offsets: {offsets[:10]}")  # Show first 10

    if not found:
        print("  No common image signatures found")

    return found

def analyze_car_structure(file_path):
    """Analyze the CAR file structure"""
    print("=" * 60)
    print(f"Analyzing: {file_path}")
    print("=" * 60 + "\n")

    # Parse BOM header
    print("=== BOM Header ===\n")
    header = read_bom_header(file_path)

    if header:
        # Search for strings
        strings = search_for_strings(file_path, min_length=5)

        # Search for images
        search_for_image_signatures(file_path)

        # Look for asset names
        print("\n=== Potential asset names ===\n")
        asset_keywords = ['icon', 'image', 'logo', 'button', 'background', 'bg',
                         'img', 'pic', 'photo', 'thumb', 'banner', '.png', '.jpg',
                         '.pdf', '@2x', '@3x', 'dark', 'light']

        for s in strings:
            lower = s.lower()
            if any(kw in lower for kw in asset_keywords):
                print(f"  {s}")

if __name__ == "__main__":
    file_path = r"D:\Downloads\qora-core-master-final\app\theme\qorai\mac\Assets.car"

    if not os.path.exists(file_path):
        print(f"Error: File not found: {file_path}")
        sys.exit(1)

    analyze_car_structure(file_path)
