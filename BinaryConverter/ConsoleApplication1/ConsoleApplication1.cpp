#define MAPX (40)
#define MAPY (40)

enum class Type
{
	None = 0x00,
	Player = 0x01,

	Goal = 0x04,
	Wall = 0x05,
	Floor = 0x06,

	Enemy = 0x07,
};

enum class Box
{
	Exists = 0x02,
	None = 0x03,
};

int main()
{
	std::cout << "\n-------------------------------------- Binary File Converter --------------------------------------\n\n";

	while (1)
	{

		FILE* file;
		char filename[256];
		std::cout << "File Name Input : ";
		std::cin >> filename;

		file = fopen(filename, "r");

		if (file == NULL)
		{
			std::cout << "File Load Failed" <<std::endl;
			continue;
		}

		//char word;
		//for (int i = 0; i < MAPX*MAPY; i++)
		//{
		//	word[i]
		//}

		char map[MAPY][MAPX];
		std::unique_ptr<Type[]> type;
		std::unique_ptr<Box[]> box;

		for (int y = 0; y < MAPY; y++)
			for (int x = 0; x < MAPX; x++)
				map[y][x] = NULL;

		unsigned int sizeX = 0, sizeY = 0;

		for (int y = 0; y < MAPY; y++)
		{
			fgets(map[y], MAPX, file);
		}
		fclose(file);

		for (unsigned int y = 0; y < MAPY; y++)
		{
			for (unsigned int x = 0; x < MAPX; x++)
			{
				switch (map[y][x])
				{
				case 'L':
					if (x > sizeX)
						sizeX = x;
					break;
				case 'C':
					if (y > sizeY)
						sizeY = y;
					break;
				default:
					break;
				}
			}
		}

		type = std::make_unique<Type[]>(sizeX*sizeY);
		box = std::make_unique<Box[]>(sizeX*sizeY);

		unsigned int writecount = 0;

		for (unsigned int y = 0; y < sizeY; y++)
		{
			for (unsigned int x = 0; x < sizeX; x++)
			{
				switch (map[y][x])
				{
				case 'P':
					type[writecount] = Type::Player;
					box[writecount] = Box::None;
					break;
				case 'E':
					type[writecount] = Type::Enemy;
					box[writecount] = Box::None;
					break;
				case '.':
					type[writecount] = Type::Floor;
					box[writecount] = Box::None;
					break;
				case 'M':
					type[writecount] = Type::Wall;
					box[writecount] = Box::None;
					break;
				case 'B':
					type[writecount] = Type::Floor;
					box[writecount] = Box::Exists;
					break;
				case 'G':
					type[writecount] = Type::Goal;
					box[writecount] = Box::None;
					break;
				case 'X':
					type[writecount] = Type::Goal;
					box[writecount] = Box::Exists;
					break;
				case 'L':
				case 'C':
				case 0x0D:
				case 0x0A:
					break;
				default:
					type[writecount] = Type::None;
					box[writecount] = Box::None;
					break;
				}
				char i = (char)type[writecount];
				char a = (char)box[writecount];

				writecount++;
			}
		}


		char outputfile[256];
		std::cout << "File Name Ouput : ";
		std::cin >> outputfile;

		file = fopen(outputfile, "wb");

		char* output = new char[2 + (sizeX*sizeY) * 2];

		output[0] = sizeX;
		output[1] = sizeY;

		for (unsigned int i = 0; i < sizeY*sizeX; i++)
		{
			output[i + 2] = (char)type[i];
		}
		for (unsigned int i = 0; i < sizeY*sizeX; i++)
		{
			output[i + 2 + sizeX * sizeY] = (char)box[i];
		}

		char a = output[11 + 2 + sizeX * sizeY];
		char b = output[12 + 2 + sizeX * sizeY];
		char c = output[13+2+ sizeX * sizeY];

		fwrite(output, sizeof(char), 2 + (sizeX * sizeY) * 2, file);

		fclose(file);

		delete[] output;
	}
}
