#include <chapter3/stack.hpp>
#include <iostream>
using namespace std;

void UseStack();
void UseSqstack();
void UseSqqueue();
void UseLinkqueue();

int main()
{
    UseStack();

    return 0;
}

void UseStack()
{
    Stack<int> s;

    if (s.IsEmpty())
    {
        cout << "Is Empty\n";
    }

    s.Push(3);
    s.Push(60);

    cout << s.Size() << endl;

    return;
}
