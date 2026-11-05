# BTLCAP (Bottlecaps)

*"Because the Future is Worth Saving For"*

BTLCAP is a SHA-256 Proof-of-Work cryptocurrency and wasteland collectible platform inspired by the post-apocalyptic currency from the Fallout universe. Built on battle-tested Bitcoin Core consensus with modern enhancements including real-time LWMA difficulty adjustment, native Bech32 `btlcap1…` SegWit addresses, and an AuxPoW merged-mined sidechain for digital bottlecap collectibles.

---

## Specification

| Parameter | Value |
|---|---|
| **Coin Name** | Bottlecaps (BTLCAP) |
| **Ticker** | BCAP |
| **Algorithm** | SHA-256d (ASIC & CPU compatible) |
| **Block Time** | 300 seconds (5 minutes) |
| **Block Reward** | 500 BCAP |
| **Halving Interval** | 420,000 blocks (~4 years) |
| **Ultimate Supply** | 420,470,000 BCAP |
| **Difficulty Algorithm** | LWMA-1 (Linear Weighted Moving Average, retargets every block) |
| **Coinbase Maturity** | 200 blocks (pool payout threshold: 50 blocks) |
| **Address Prefixes** | `btlcap1…` (Native Bech32 SegWit) / `B…` (Legacy P2PKH) |
| **P2P Port** | 12566 |
| **RPC Port** | 12567 |
| **Merged-Mining Sidechain** | Bottlecaps (CAPC) AuxPoW Collectibles & The Forge |

---

## Ecosystem & Infrastructure

- **Official Website:** [caps-core.undergroundroots.ca](https://caps-core.undergroundroots.ca)
- **White Paper:** [caps-core.undergroundroots.ca/whitepaper/](https://caps-core.undergroundroots.ca/whitepaper/)
- **Block Explorer:** [caps.undergroundroots.ca](https://caps.undergroundroots.ca)
- **Web Wallet:** [wallet.undergroundroots.ca](https://wallet.undergroundroots.ca)
- **Mining Pool:** [asicpool.space](https://asicpool.space) (Stratum ports: 8433 general / 8434 nerdminer / 8435 rental / 8439 solo)
- **Mobile Vault App:** Caps Vault (Android APK) — Key management, biometric vault, and bottlecap collection viewer.

---

## Bottlecaps (CAPC) Sidechain & Digital Collectibles

BTLCAP features an AuxPoW (Auxiliary Proof-of-Work) merged-mined sidechain:
- **Zero Energy Overhead:** Mainnet miners simultaneously secure the sidechain without requiring additional hashing power or electricity.
- **Random Card Drops:** Every block mined on the pool triggers automatic 1-of-1 wasteland bottlecap trading cards dropped directly to miner addresses across 5 rarity tiers (Scrap, Brass, Silver, Gilded Gold, and Quantum Glow).
- **The Wasteland Forge Studio:** Spend 50 BCAP in the Web Wallet or Mobile Vault to hand-draw custom emblems or upload custom badge artwork, permanently minting your 1-of-1 design to the chain.
- **Single-Use Seals:** Cryptographically anchored to UTXOs (`CAPC\x02` OP_TRANSFER and `CAPC\x04` OP_FORGE) for verifiable ownership and direct wallet-to-wallet trading.

---

## Getting Started

### Prerequisites
- **OS:** Linux (Ubuntu 20.04+), Windows (MSVC or MinGW), macOS
- **Dependencies:** `build-essential`, `libtool`, `autotools-dev`, `automake`, `pkg-config`, `bsdmainutils`, `python3`

### Building from Source (Linux)
```bash
git clone https://github.com/ShaeOJ/Caps-new.git
cd Caps-new
./autogen.sh
./configure --disable-tests --disable-bench
make -j$(nproc)
```

### Running a Full Node
Create `~/.caps/caps.conf`:
```ini
server=1
daemon=1
txindex=1
rpcuser=your_rpc_user
rpcpassword=your_secure_password
addnode=caps.undergroundroots.ca
```

Start the daemon:
```bash
./src/capsd
```

Check blockchain sync:
```bash
./src/caps-cli getblockchaininfo
```

---

## License

BTLCAP is released under the terms of the MIT license. See [COPYING](COPYING) for more information.
