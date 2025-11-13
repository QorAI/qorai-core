import struct

filename = r"D:\Downloads\qora-core-master-final\all_blocks\block_0044_21938bytes.dat"

with open(filename, 'rb') as f:
    data = f.read()

print("="*60)
print("Analyzing CTSI TLV Structure")
print("="*60)
print(f"File: {filename}")
print(f"Total size: {len(data)} bytes\n")

print("Header Analysis:")
print(f"  Magic: {data[0:4]}")
print(f"  Dimensions: {struct.unpack('<II', data[12:20])}")
print(f"  Pixel format bytes: {data[20:24].hex()}\n")

print("TLV Section (starting at offset 184):")
print(f"  First 32 bytes: {data[184:216].hex()}\n")

# Parse TLV entries - Try LITTLE-ENDIAN
print("Trying little-endian parsing:\n")
offset = 184
tlv_entries = []

while offset < len(data) - 8:
    tag = struct.unpack('<I', data[offset:offset+4])[0]
    length = struct.unpack('<I', data[offset+4:offset+8])[0]

    if length == 0 or length > len(data) - offset - 8 or length > 50000:
        print(f"TLV parsing ended at offset {offset}")
        print(f"  Remaining data starts at: {offset}")
        print(f"  Remaining data size: {len(data) - offset} bytes")
        print(f"  Last tag: 0x{tag:08X}, length: {length}")
        break

    print(f"TLV Entry at offset {offset}:")
    print(f"  Tag: 0x{tag:08X} ({tag})")
    print(f"  Length: {length} bytes")

    # Show first few bytes of value
    value_start = offset + 8
    value_preview = data[value_start:value_start+min(32, length)]
    print(f"  Value preview: {value_preview.hex()}")

    # Check if this looks like compressed data
    if length > 100:
        # Check for zlib magic bytes
        if value_preview[0:2] == b'\x78\x9c' or value_preview[0:2] == b'\x78\xda':
            print(f"  ** Looks like zlib compressed data!")

    print()

    tlv_entries.append({
        'offset': offset,
        'tag': tag,
        'length': length,
        'value_offset': value_start
    })

    offset += 8 + length

print(f"\nTotal TLV entries: {len(tlv_entries)}")
print(f"Data after TLV starts at: {offset}")
print(f"Remaining bytes: {len(data) - offset}")
