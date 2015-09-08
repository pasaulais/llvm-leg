int foo(int x) __attribute__((noinline));
int foo(int x)
{
    return x * 3;
}

int bar(int x)
{
    return foo(x - 5);
}
