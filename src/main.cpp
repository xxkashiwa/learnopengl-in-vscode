// 声明各个 lecture 的入口函数
int main01();
int main02();
int main03();
int main04();
int main05();
int main06();
int main()
{
	unsigned int lectureIndex = 6;

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
	case 6:
		return main06();
	default:
		return 0;
	}
}
