#include <iostream>

class Singleton
{
public:
	// 获取单例实例对象
	static Singleton &GetInstance()
	{
		// 利用局部静态变量实现单例
		static Singleton instance;
		return instance;
	}

	// 打印单例的地址
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
};

int main()
{
	Singleton::GetInstance().print();
	return 0;
}
