import zlib
import liblzfse

filename = r"D:\Downloads\qora-core-master-final\all_blocks\block_0044_21938bytes.dat"

with open(filename, 'rb') as f:
    data = f.read()

# Data starts at offset 297
compressed = data[297:]

print(f"Compressed data size: {len(compressed)} bytes")
print(f"First 16 bytes: {compressed[:16].hex()}")
print(f"Expected uncompressed size: {256*256*4} bytes\n")

# Try zlib
print("1. Trying zlib...")
try:
    result = zlib.decompress(compressed)
    print(f"   SUCCESS! Decompressed size: {len(result)} bytes")
except Exception as e:
    print(f"   Failed: {e}")

# Try deflate (raw)
print("\n2. Trying deflate (raw)...")
try:
    result = zlib.decompress(compressed, -15)
    print(f"   SUCCESS! Decompressed size: {len(result)} bytes")
except Exception as e:
    print(f"   Failed: {e}")

# Try LZFSE
print("\n3. Trying LZFSE...")
try:
    result = liblzfse.decompress(compressed)
    print(f"   SUCCESS! Decompressed size: {len(result)} bytes")
except Exception as e:
    print(f"   Failed: {e}")

# Try with zlib header added
print("\n4. Trying with zlib header...")
try:
    # Add zlib header
    with_header = b'\x78\x9c' + compressed
    result = zlib.decompress(with_header)
    print(f"   SUCCESS! Decompressed size: {len(result)} bytes")
except Exception as e:
    print(f"   Failed: {e}")

# Check if it's already uncompressed but with some header
print("\n5. Check if data is actually uncompressed...")
print(f"   Available data: {len(compressed)} bytes")
print(f"   Expected: {256*256*4} bytes")
print(f"   Ratio: {len(compressed) / (256*256*4):.2%}")
