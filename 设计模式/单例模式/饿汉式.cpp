#include <iostream>
#include <thread>

class Singleton
{
public:
	// 获取单例
	static Singleton *GetInstance()
	{
		return pInstance;
	}
	// 释放单例, 进程退出时调用
	static void DeleteInstance()
	{
		if (pInstance != nullptr)
		{
			delete pInstance;
			pInstance = nullptr;
		}
	}

	//打印单例的地址
	void print()
	{
		std::cout << this << std::endl;
	}

private:
	// 禁止外部构造和析构
	Singleton() = default;
	~Singleton() = default;

	// 禁止外部拷贝或赋值
	Singleton(const Singleton &) = default;
	Singleton &operator=(const Singleton &);

	// 唯一单例对象指针
	static Singleton *pInstance;
};

// 代码一运行就初始化实例, 本身就线程安全
Singleton *Singleton::pInstance = new (std::nothrow) Singleton;

int main()
{
	Singleton::GetInstance()->print();
	return 0;
}