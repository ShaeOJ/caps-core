#!/usr/bin/env python3
"""
Genesis Block Miner for Caps
Mines a new genesis block with SHA256d
"""

import hashlib
import struct
import time

def sha256d(data):
    """Double SHA256 hash"""
    return hashlib.sha256(hashlib.sha256(data).digest()).digest()

def uint256_from_str(s):
    """Convert bytes to integer"""
    r = 0
    t = s[::-1]
    for i, c in enumerate(t):
        r += c << (i * 8)
    return r

def ser_uint256(u):
    """Serialize uint256 to bytes"""
    rs = b""
    for _ in range(8):
        rs += struct.pack("<I", u & 0xFFFFFFFF)
        u >>= 32
    return rs

def compact_to_uint256(nBits):
    """Convert compact format to uint256"""
    nSize = nBits >> 24
    nWord = nBits & 0x007fffff
    if nSize <= 3:
        nWord >>= 8 * (3 - nSize)
    else:
        nWord <<= 8 * (nSize - 3)
    return nWord

def create_coinbase_script(timestamp):
    """Create the coinbase scriptSig"""
    # Bitcoin genesis format: 04ffff001d0104 + len(timestamp) + timestamp
    script = bytes([0x04, 0xff, 0xff, 0x00, 0x1d])  # nBits in script
    script += bytes([0x01, 0x04])  # Push 0x04
    script += bytes([len(timestamp)])  # Push length
    script += timestamp.encode('utf-8')
    return script

def create_coinbase_tx(timestamp, pubkey_hex, reward=0):
    """Create the coinbase transaction"""
    # Transaction version
    tx = struct.pack("<I", 1)

    # Number of inputs
    tx += bytes([1])

    # Previous output (null for coinbase)
    tx += bytes(32)  # Previous tx hash (all zeros)
    tx += struct.pack("<I", 0xFFFFFFFF)  # Previous output index

    # ScriptSig
    scriptsig = create_coinbase_script(timestamp)
    tx += bytes([len(scriptsig)])
    tx += scriptsig

    # Sequence
    tx += struct.pack("<I", 0xFFFFFFFF)

    # Number of outputs
    tx += bytes([1])

    # Output value (reward in satoshis)
    tx += struct.pack("<Q", reward)

    # ScriptPubKey: OP_PUSHBYTES + pubkey + OP_CHECKSIG
    pubkey = bytes.fromhex(pubkey_hex)
    scriptpubkey = bytes([len(pubkey)]) + pubkey + bytes([0xAC])  # OP_CHECKSIG = 0xAC
    tx += bytes([len(scriptpubkey)])
    tx += scriptpubkey

    # Locktime
    tx += struct.pack("<I", 0)

    return tx

def calc_merkle_root(txhash):
    """Calculate merkle root from single transaction"""
    return txhash  # For single tx, merkle root = tx hash

def create_block_header(version, prev_hash, merkle_root, ntime, nbits, nonce):
    """Create block header"""
    header = struct.pack("<I", version)
    header += prev_hash
    header += merkle_root
    header += struct.pack("<I", ntime)
    header += struct.pack("<I", nbits)
    header += struct.pack("<I", nonce)
    return header

def mine_genesis():
    # Genesis parameters for Caps
    timestamp = "Caps - Because the Future is Worth Saving For"
    pubkey_hex = "04423ef45ccb4dc584e8b617789ee4cf108ae18b1cae979eb7cd7f3c69b538e3f888e8efd8dab0b0777baff8871f96b116b47576b731bdeaad005ee7492ceb592c"
    ntime = 1738368000  # Feb 1, 2026
    nbits = 0x1e0ffff0
    version = 1
    reward = 0  # 0 COIN for genesis

    # Calculate target from nBits
    target = compact_to_uint256(nbits)

    print("=" * 60)
    print("Caps Genesis Block Miner")
    print("=" * 60)
    print(f"Timestamp: {timestamp}")
    print(f"nTime: {ntime}")
    print(f"nBits: 0x{nbits:08x}")
    print(f"Target: {target:064x}")
    print("=" * 60)

    # Create coinbase transaction
    coinbase_tx = create_coinbase_tx(timestamp, pubkey_hex, reward)
    tx_hash = sha256d(coinbase_tx)
    merkle_root = calc_merkle_root(tx_hash)

    print(f"Merkle Root: {merkle_root[::-1].hex()}")
    print("=" * 60)
    print("Mining...")

    # Previous block hash (all zeros for genesis)
    prev_hash = bytes(32)

    nonce = 0
    start_time = time.time()
    last_report = start_time

    while True:
        header = create_block_header(version, prev_hash, merkle_root, ntime, nbits, nonce)
        block_hash = sha256d(header)
        hash_int = uint256_from_str(block_hash)

        if hash_int <= target:
            elapsed = time.time() - start_time
            print("\n" + "=" * 60)
            print("GENESIS BLOCK FOUND!")
            print("=" * 60)
            print(f"nTime: {ntime}")
            print(f"nNonce: {nonce}")
            print(f"hashGenesisBlock: 0x{block_hash[::-1].hex()}")
            print(f"hashMerkleRoot: 0x{merkle_root[::-1].hex()}")
            print(f"Mining time: {elapsed:.2f} seconds")
            print("=" * 60)

            # Output in C++ format for chainparams.cpp
            print("\n// Copy these values to chainparams.cpp:")
            print(f'genesis = CreateGenesisBlock({ntime}, {nonce}, 0x{nbits:08x}, 1, 0 * COIN);')
            print(f'assert(consensus.hashGenesisBlock == uint256S("0x{block_hash[::-1].hex()}"));')
            print(f'assert(genesis.hashMerkleRoot == uint256S("0x{merkle_root[::-1].hex()}"));')
            break

        nonce += 1

        # Progress report every 5 seconds
        current_time = time.time()
        if current_time - last_report >= 5:
            hashrate = nonce / (current_time - start_time)
            print(f"nNonce: {nonce:>10} | Hash: {block_hash[::-1].hex()[:16]}... | {hashrate:.0f} H/s")
            last_report = current_time

        # Handle nonce overflow
        if nonce >= 0xFFFFFFFF:
            print("Nonce wrapped, incrementing time")
            nonce = 0
            ntime += 1

if __name__ == "__main__":
    mine_genesis()
