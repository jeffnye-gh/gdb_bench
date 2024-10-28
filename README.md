Jeff Nye, 2024
 
# gdb_bench

Exeriments with simulator control and gdb interfaces.

Uses gdb-server from Embecosm and spdlog from gabime. See .gitmodules.

Early stage development

# Usage

```
git clone --recursive git@github.com:jeffnye-gh/gdb_bench.git
make
```

Modify scripts/compile.sh to point to your riscv compiler.

In another terminal
``` 
cd scripts
bash compile.sh

target remote :1234
```

