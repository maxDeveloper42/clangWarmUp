### basic compile commands

gcc hello.c -o hello

gcc -g main.c -o out

---

### how to save your output and append files 

- `>>`: append. Adds text to the end of the file; original content remains.
- `>`: overwrite. Erases the file first, then writes new text.

---

# Summary
1. **`sizeof`**: compile-time operator (not function), returns `size_t` (unsigned).
   - Fixed array: GCC precomputes total bytes; `sizeof(arr)/sizeof(arr[0])` gets element count.
   - VLA (C99): `sizeof` calculated at runtime via inline instructions.
   - Array as function parameter → decays to pointer, `sizeof` returns pointer size.
2. **C array**: contiguous memory, zero-indexed; `arr[i] = *(arr+i)`; no out-of-bounds check.
3. **Struct array**: valid, each element is a struct; access members with `arr[i].member`.
4. **Hex**: `0xF` = 4 bits; two hex digits = 1 byte (`0xFF`).
5. **GDB**: inspect assembly to verify compile-time constant evaluation for `sizeof` on fixed arrays.


---

try to searh a funct:

```bash
grep -rn "printf"
```


