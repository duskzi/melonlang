# Melon Lang

This is the official repository for the melon language interpreter.

---

### What differs Melong from other interpreted languages?

Melon was designed to be simple, type-safe and lightweight, even though it's not as performant as other languages.

Melon offers a C-like syntax and easy-to-use standard library (in development). 

### How Melon Lang looks like?

> main.mln
```
@lib <io>
@lib <./libs/mycustomlib.mln>

Code main(void) {

    | This is a comment
    out("Hello from Melon!");

    | I really don't know if it's good to
    | return a code status here but I'll keep
    return CodeOk; 
}
```

### Why the name "Melon"? 

Because the language looks juicy, delicious and watery.

Just kidding, it's because I had its idea while eating a melon.

