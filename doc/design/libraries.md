# Libraries

| Name                     | Description |
|--------------------------|-------------|
| *libcaps_cli*         | RPC client functionality used by *caps-cli* executable |
| *libcaps_common*      | Home for common functionality shared by different executables and libraries. Similar to *libcaps_util*, but higher-level (see [Dependencies](#dependencies)). |
| *libcaps_consensus*   | Stable, backwards-compatible consensus functionality used by *libcaps_node* and *libcaps_wallet* and also exposed as a [shared library](../shared-libraries.md). |
| *libcapsconsensus*    | Shared library build of static *libcaps_consensus* library |
| *libcaps_kernel*      | Consensus engine and support library used for validation by *libcaps_node* and also exposed as a [shared library](../shared-libraries.md). |
| *libcapsqt*           | GUI functionality used by *caps-qt* and *caps-gui* executables |
| *libcaps_ipc*         | IPC functionality used by *caps-node*, *caps-wallet*, *caps-gui* executables to communicate when [`--enable-multiprocess`](multiprocess.md) is used. |
| *libcaps_node*        | P2P and RPC server functionality used by *capsd* and *caps-qt* executables. |
| *libcaps_util*        | Home for common functionality shared by different executables and libraries. Similar to *libcaps_common*, but lower-level (see [Dependencies](#dependencies)). |
| *libcaps_wallet*      | Wallet functionality used by *capsd* and *caps-wallet* executables. |
| *libcaps_wallet_tool* | Lower-level wallet functionality used by *caps-wallet* executable. |
| *libcaps_zmq*         | [ZeroMQ](../zmq.md) functionality used by *capsd* and *caps-qt* executables. |

## Conventions

- Most libraries are internal libraries and have APIs which are completely unstable! There are few or no restrictions on backwards compatibility or rules about external dependencies. Exceptions are *libcaps_consensus* and *libcaps_kernel* which have external interfaces documented at [../shared-libraries.md](../shared-libraries.md).

- Generally each library should have a corresponding source directory and namespace. Source code organization is a work in progress, so it is true that some namespaces are applied inconsistently, and if you look at [`libcaps_*_SOURCES`](../../src/Makefile.am) lists you can see that many libraries pull in files from outside their source directory. But when working with libraries, it is good to follow a consistent pattern like:

  - *libcaps_node* code lives in `src/node/` in the `node::` namespace
  - *libcaps_wallet* code lives in `src/wallet/` in the `wallet::` namespace
  - *libcaps_ipc* code lives in `src/ipc/` in the `ipc::` namespace
  - *libcaps_util* code lives in `src/util/` in the `util::` namespace
  - *libcaps_consensus* code lives in `src/consensus/` in the `Consensus::` namespace

## Dependencies

- Libraries should minimize what other libraries they depend on, and only reference symbols following the arrows shown in the dependency graph below:

<table><tr><td>

```mermaid

%%{ init : { "flowchart" : { "curve" : "basis" }}}%%

graph TD;

caps-cli[caps-cli]-->libcaps_cli;

capsd[capsd]-->libcaps_node;
capsd[capsd]-->libcaps_wallet;

caps-qt[caps-qt]-->libcaps_node;
caps-qt[caps-qt]-->libcapsqt;
caps-qt[caps-qt]-->libcaps_wallet;

caps-wallet[caps-wallet]-->libcaps_wallet;
caps-wallet[caps-wallet]-->libcaps_wallet_tool;

libcaps_cli-->libcaps_util;
libcaps_cli-->libcaps_common;

libcaps_common-->libcaps_consensus;
libcaps_common-->libcaps_util;

libcaps_kernel-->libcaps_consensus;
libcaps_kernel-->libcaps_util;

libcaps_node-->libcaps_consensus;
libcaps_node-->libcaps_kernel;
libcaps_node-->libcaps_common;
libcaps_node-->libcaps_util;

libcapsqt-->libcaps_common;
libcapsqt-->libcaps_util;

libcaps_wallet-->libcaps_common;
libcaps_wallet-->libcaps_util;

libcaps_wallet_tool-->libcaps_wallet;
libcaps_wallet_tool-->libcaps_util;

classDef bold stroke-width:2px, font-weight:bold, font-size: smaller;
class caps-qt,capsd,caps-cli,caps-wallet bold
```
</td></tr><tr><td>

**Dependency graph**. Arrows show linker symbol dependencies. *Consensus* lib depends on nothing. *Util* lib is depended on by everything. *Kernel* lib depends only on consensus and util.

</td></tr></table>

- The graph shows what _linker symbols_ (functions and variables) from each library other libraries can call and reference directly, but it is not a call graph. For example, there is no arrow connecting *libcaps_wallet* and *libcaps_node* libraries, because these libraries are intended to be modular and not depend on each other's internal implementation details. But wallet code is still able to call node code indirectly through the `interfaces::Chain` abstract class in [`interfaces/chain.h`](../../src/interfaces/chain.h) and node code calls wallet code through the `interfaces::ChainClient` and `interfaces::Chain::Notifications` abstract classes in the same file. In general, defining abstract classes in [`src/interfaces/`](../../src/interfaces/) can be a convenient way of avoiding unwanted direct dependencies or circular dependencies between libraries.

- *libcaps_consensus* should be a standalone dependency that any library can depend on, and it should not depend on any other libraries itself.

- *libcaps_util* should also be a standalone dependency that any library can depend on, and it should not depend on other internal libraries.

- *libcaps_common* should serve a similar function as *libcaps_util* and be a place for miscellaneous code used by various daemon, GUI, and CLI applications and libraries to live. It should not depend on anything other than *libcaps_util* and *libcaps_consensus*. The boundary between _util_ and _common_ is a little fuzzy but historically _util_ has been used for more generic, lower-level things like parsing hex, and _common_ has been used for caps-specific, higher-level things like parsing base58. The difference between util and common is mostly important because *libcaps_kernel* is not supposed to depend on *libcaps_common*, only *libcaps_util*. In general, if it is ever unclear whether it is better to add code to *util* or *common*, it is probably better to add it to *common* unless it is very generically useful or useful particularly to include in the kernel.


- *libcaps_kernel* should only depend on *libcaps_util* and *libcaps_consensus*.

- The only thing that should depend on *libcaps_kernel* internally should be *libcaps_node*. GUI and wallet libraries *libcapsqt* and *libcaps_wallet* in particular should not depend on *libcaps_kernel* and the unneeded functionality it would pull in, like block validation. To the extent that GUI and wallet code need scripting and signing functionality, they should be get able it from *libcaps_consensus*, *libcaps_common*, and *libcaps_util*, instead of *libcaps_kernel*.

- GUI, node, and wallet code internal implementations should all be independent of each other, and the *libcapsqt*, *libcaps_node*, *libcaps_wallet* libraries should never reference each other's symbols. They should only call each other through [`src/interfaces/`](`../../src/interfaces/`) abstract interfaces.

## Work in progress

- Validation code is moving from *libcaps_node* to *libcaps_kernel* as part of [The libcapskernel Project #24303](https://github.com/MrVistos/caps/issues/24303)
- Source code organization is discussed in general in [Library source code organization #15732](https://github.com/MrVistos/caps/issues/15732)
