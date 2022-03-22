#ifdef __BORLANDC__

#include <memory.stl>
#include <new.h>

int main()
{
	int *p = allocator<int>().allocate(512);
	allocator<int>().deallocate(p, 512);
}

#endif
