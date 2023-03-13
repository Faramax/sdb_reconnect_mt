int main()
{
   return 0;
}

struct A
{
   int a = 8;
   int b = 4;
   int c = 3;
};

extern "C" {
void _exit(int __status)
{
   struct A a;
   while(1);
}
}
