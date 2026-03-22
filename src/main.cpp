// 声明各个 lecture 的入口函数
int main01();
int main02();
int main03();
int main04();
int main05();
int main()
{
	unsigned int lectureIndex = 5;

	switch (lectureIndex)
	{
	case 1:
		return main01();
	case 2:
		return main02();
	case 3:
		return main03();
	case 4:
		return main04();
	case 5:
		return main05();
	default:
		return 0;
	}
}
