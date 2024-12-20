#include <Pool.class.hpp>
#include <string.h>

Pool::Pool(): _idx(0), _size(POOL_SIZE)
{
	_pool.reserve(POOL_SIZE);
}

Pool::~Pool()
{
}

Node*	Pool::next()
{
	if (_idx == _size)
		return (nullptr);
	else
	{
		_pool.emplace_back(Node());
		Node* pt = &_pool[_idx];
		_idx++;
		return (pt);
	}
}

PoolStack::PoolStack()
{
	_poolStack.push_back(new Pool());
	_size = 1;
	_memoryUsed = 0;
}

Node*	PoolStack::next()
{
	Node* pt = nullptr;
	if (!_recycle.empty())
	{
		pt = _recycle.back();
		_recycle.pop_back();
		return (pt);
	}
	pt = _poolStack.back()->next();
	if (pt == nullptr)
	{
		if (_memoryUsed > MAX_MEMORY_KB)
			throw std::overflow_error("too much memory used");
		_poolStack.push_back(new Pool());
		_size++;

		updateMemoryUsed();
		return this->next();
	}

	return pt;
}

void	PoolStack::recycle(Node *p)
{
	_recycle.push_back(p);
}

int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

void	PoolStack::updateMemoryUsed() {
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    _memoryUsed = result;
}
