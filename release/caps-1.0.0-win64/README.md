# Caps (CAPS)

*"Because the Future is Worth Saving For"*

Caps is a SHA256 Proof-of-Work cryptocurrency inspired by the post-apocalyptic currency from the Fallout universe. Built as a community-driven project with a focus on stability and decentralization.

## Overview

Caps aims to provide:
- **Reliable Transactions**: A stable and secure network for value transfer
- **Community Focus**: Open-source development driven by the community
- **Accessibility**: Easy to mine with standard SHA256 hardware

## Features

- **SHA256 Mining**: Compatible with existing Bitcoin ASIC miners
- **Security**: Battle-tested consensus protocol from Bitcoin Core
- **Scalability**: Optimized for efficient transaction processing
- **Community-Driven**: Open-source project with contributions from developers worldwide

## Specification

<table>
<tr><td>Coin Name</td><td>Caps</td></tr>
<tr><td>Ticker</td><td>CAPS</td></tr>
<tr><td>Type</td><td>PoW (SHA256)</td></tr>
<tr><td>Maturity</td><td>200</td></tr>
<tr><td>Max supply</td><td>21 000 000</td></tr>
<tr><td>P2P port</td><td>12566</td></tr>
<tr><td>RPC port</td><td>12567</td></tr>
<tr><td>Prefix</td><td>"C" / "caps1"</td></tr>
<tr><td>Halving</td><td>210 000</td></tr>
<tr><td>Block time</td><td>300 seconds</td></tr>
<tr><td>Diff time</td><td>~96 blocks</td></tr>
<tr><td>Block reward</td><td>50</td></tr>
<tr><td>Algo</td><td>SHA256</td></tr>
</table>

## Getting Started

### Prerequisites

Before you begin, ensure you have met the following requirements:
- **Operating System**: Linux, macOS, or Windows.
- **Dependencies**: Ensure you have `git`, `cmake`, and `gcc` or equivalent installed.

### Installation

1. **Clone the Repository**
```bash
   git clone https://github.com/AquaCaps/caps.git
   cd caps
```

2. **Build the Source Code**
```bash
   make clean
   make distclean
   ./autogen.sh
   # for linux:
   ./configure --disable-tests --disable-bench # possible arguments: --with-gui=qt5 --disable-wallet --without-gui
   make
   # for windows:
   make clean
   cd depends
   make HOST=x86_64-w64-mingw32
   cd ..
   ./configure --prefix=`pwd`/depends/x86_64-w64-mingw32 --with-gui=qt5 --disable-tests --disable-bench
   make
```

   3. **Run the Node**
```bash
   ./capsd
```
## Usage

### Wallet Setup

1.  **Generate a New Wallet**
```bash
   ./caps-cli createwallet "mywallet"
```
    
-   **Get Wallet Address**
```bash
   ./caps-cli getnewaddress
```
### Mining

Start mining with the following command:
```bash
  ./caps-cli generatetoaddress n "mywalletaddress"
```
Replace `n` with the number of blocks you want to mine and `"mywalletaddress"` with your actual wallet address.

## Contributing

We welcome contributions from the community! To get started:

1.  Fork the repository on GitHub.
2.  Create a new branch (`git checkout -b feature/YourFeature`).
3.  Make your changes and commit them (`git commit -am 'Add new feature'`).
4.  Push to the branch (`git push origin feature/YourFeature`).
5.  Create a new Pull Request.

### Reporting Issues

If you encounter any issues, please report them on our [GitHub Issues](https://github.com/bitcoin-silver/core/issues) page.
