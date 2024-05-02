#include <fstream>
#include <iostream>

char* temp;

inline static void printl(const char* start, uint8_t length)
{
	for (uint8_t i = 0; i < length; i++)
		putchar(start[i]);
}

char tt[200];

struct Pair
{
	char* word;
	long wordLength;
	float d[300];

	inline void print()
	{
		printl(word, wordLength);
	}

	inline bool check(char* str) const
	{
		if (wordLength <= 1)
			return false;
		for (int i = 0; i < wordLength; i++)
		{
			if (*str == '\0' || tolower(word[i]) != str[i])
				return false;
		}
		return true;
	}

	inline float diff(Pair* pair) const
	{
		float x = 0, t;
		for (int i = 0; i < 300; i++)
		{
			t = d[i] - pair->d[i];
			x += t * t;
		}
		return x;
	}
};

Pair* Data;

#define max(a, b) ((a) < (b) ? (b) : (a))

int main()
{
	Data = (Pair*)malloc(840000 * sizeof(Pair));

	std::ifstream file("ENTER_PATH/glove.840B.300d.txt");

	file.seekg(0, std::ios::end);
	size_t file_size = file.tellg();
	file.seekg(0, std::ios::beg);

	temp = (char*)malloc(1000002);
	file.read(temp, file_size);
	file.close();
	int state = 1;
	unsigned long long I = 0;
	int d = 300;
	file_size -= 100;
	for (unsigned long long i = 0; i < file_size; i++)
	{
		char* c = temp + i;
		if (*c == '\n')
		{
			state = 1;
		}
		else if (*c == ' ')
		{
			state = 2;
		}
		else
		{
			char* t = c;
			while (*c != ' ' && *c != '\n') c++;
			long length = c - t;
			i += length - 1;

			if (state == 1)
			{
				Data[I].word = t;
				Data[I].wordLength = length;
				if (d != 300)
					abort();
				d = 0;
				I++;
				if (I == 8400000)
					break;
			}
			else
			{
				memcpy(tt, c, length);
				tt[length] = 0;
				Data[I].d[d] = atof(tt);
				d++;
			}

			state = 0;
		}
	}

	std::cout << I << std::endl;

	for (int i = 0; i < 5; i++)
	{
		std::cin >> tt;

		std::cout << tt << '\n';

		Pair* pair = NULL;
		for (unsigned long long i = 0; i < I; i++)
		{
			if (Data[i].check(tt))
			{
				pair = &Data[i];
				break;
			}
		}

		if (pair == NULL)
		{
			std::cout << "wont cum";
			continue;
		}

		for (unsigned long long i = 0; i < I; i++)
		{
			if (Data[i].diff(pair) < 10.0f)
			{
				Data[i].print();
				std::cout << '\n';
			}
		}
	}

	free(temp);
	free(Data);
	return 0;
}