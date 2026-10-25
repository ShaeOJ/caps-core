# Caps Core - Project Notes

## Repository
- **Repo:** github.com/ShaeOJ/caps-core
- **Branch:** main
- **Fork of:** Bitcoin Silver (bitcoinsilver) — fully renamed to Caps

## Current State (2026-02-03)

### What's Running
- Caps node running on this machine, chain height 751+
- Stratum mining server at `M:\Node Etc\Caps_Server\stratum_server.py` (PID 33204)
- 2 miners connected: bitdsk/N5.Rexi (ASIC, ~257 GH/s) + NerdMiner
- Mining to wallet "ShaeOJ", payout address: `caps1q4x5ggld7tyy0uvk3ptqu6303p8nsfhrrtf2tve`
- LAN IP for miner connections: `10.0.0.214`
- Dashboard: http://localhost:8080 (now shows "Connect Your Miner" section with stratum URL)

### Node Config Location
- Data dir: `M:\Node Etc\Caps_Beta\data\`
- RPC: port 10567, user=capsuser, password=capspass123
- P2P: port 12566
- Stratum: port 10333
- caps-cli binary: `M:\Node Etc\Caps_Beta\caps-cli.exe`

### Uncommitted Changes in Repo
- Massive rename from bitcoinsilver -> Caps across hundreds of files (staged but not committed)
- This is pre-existing work — handle carefully, commit in logical chunks

### Recent Commits
- `e6b4fd9de5` — Replace local DNS seed IP with public seed node (pushed)
- `f30bcc7bf6` — Fix seed node port to 12566
- `4e3ed0953c` — Update seed node to 174.4.45.33

### DNS Seed Fix (done, committed, pushed & recompiled)
- `src/kernel/chainparams.cpp:135` — changed `10.0.0.20` (local) to `174.4.45.33` (public IP)
- Matches fixed seed in `chainparamsseeds.h`
- Recompiled via MSVC (Release/x64) — fresh binaries in `build_msvc\x64\Release\` and bundled into CapsMinePack

## CapsMinePack (deployable mining package)

### Location
`M:\Node Etc\CapsMinePack\`

### What It Is
Self-contained zip bundle that lets anyone extract, run `python launcher.py`, and have a full Caps node + stratum mining server running with zero manual configuration.

### Files
- `launcher.py` — Cross-platform Python 3.6+ orchestrator (8-step first-run, 4-step resume, clean Ctrl+C shutdown)
  - Prefers caps-qt (GUI wallet) over capsd (daemon), falls back gracefully
  - Auto-adds Windows firewall rules via netsh (if admin)
  - Detects LAN IP and displays miner connection info (stratum URL)
  - Waits for IBD sync + getblocktemplate readiness before starting stratum
  - caps.conf includes `addnode=174.4.45.33:12566` for peer discovery
- `README.txt` — User instructions
- `stratum/stratum_server.py` — Pip-Boy themed dashboard with miner connection info
  - Dashboard shows local IP / stratum URL in "Connect Your Miner" section
  - API returns `local_ip` and `stratum_url` fields
- `bin/capsd.exe` (21 MB) — Recompiled with seed fix (2026-02-03)
- `bin/caps-cli.exe` (2.4 MB) — Recompiled with seed fix (2026-02-03)
- `bin/caps-qt.exe` (46 MB) — GUI wallet, recompiled with seed fix (2026-02-03)

### How It Works
1. First run: generates RPC creds, writes caps.conf, sets firewall rules, starts caps-qt (or capsd), polls RPC (120s timeout), waits for IBD sync, creates "mining" wallet, generates bech32 address, writes stratum config, starts stratum
2. Subsequent runs: loads state from `data/.minepack_state.json`, starts node, waits for RPC + sync, loads wallet, starts stratum
3. Ctrl+C: stops stratum (terminate), stops capsd gracefully via caps-cli stop, waits 60s before force-kill

### Ports
| Port  | Purpose |
|-------|---------|
| 12566 | P2P     |
| 10567 | RPC     |
| 10333 | Stratum |
| 8080  | Dashboard |

### Distribution
- **Zip:** `M:\Node Etc\CapsMinePack.zip` (~27 MB, includes caps-qt) — ready to distribute
- Binaries recompiled with seed fix and bundled

### Still TODO for CapsMinePack
- Test launcher.py end-to-end on a clean machine
- Test on Linux
- Build Linux binaries for cross-platform zip

## Network Info
- Public seed node: 174.4.45.33
- Genesis hash: `000008f6047ff42c6a9b2f53960d06c79a5291e20b46030b7e2a7254a84ad01c`
- Bech32 HRP: `caps`
- Base58 pubkey prefix: 0x1C (addresses start with 'C')
- Halving interval: 210,000 blocks
- Block reward: 50 CAPS

## Build Info
- **Build system:** MSVC 2022 Community, MSBuild 17.14.19
- **Solution:** `build_msvc\caps.sln`
- **Config:** Release / x64
- **vcpkg triplet:** x64-windows-static
- **Output:** `build_msvc\x64\Release\` (also copies to `src\`)
- **Build command (PowerShell):**
  ```
  & 'C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe' capsd\capsd.vcxproj /p:Configuration=Release /p:Platform=x64 /m
  ```

## Stratum Server Details
- All block rewards go to the single `payout_address` in `config.json` — the worker name is just a display label
- Worker name can be anything (miners choose their own, e.g. `caps1q...bitdsk` or `myrig.gpu1`)
- The server does NOT parse or pay out to addresses in the worker name
- Dashboard "Connect Your Miner" section auto-detects LAN IP and shows ready-to-copy stratum URL
- Both `M:\Node Etc\Caps_Server\stratum_server.py` and `M:\Node Etc\CapsMinePack\stratum\stratum_server.py` are in sync

## Known Issues
- NerdMiner occasionally disconnects with `[WinError 121]` (Windows semaphore timeout) — auto-reconnects fine
- The large bitcoinsilver->Caps rename is uncommitted — needs to be committed in logical chunks
