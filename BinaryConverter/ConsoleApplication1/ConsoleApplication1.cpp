#define MAPX (40)
#define MAPY (40)

enum class Type
{
	Allies = 0x0A,
	Enemy = 0x0E,

	Plain = 0x01,
	Mountain = 0x02,
	Forest = 0x03,

	None = 0x00,
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
		//std::unique_ptr<Box[]> box;

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
		//box = std::make_unique<Box[]>(sizeX*sizeY);

		unsigned int writecount = 0;

		for (unsigned int y = 0; y < sizeY; y++)
		{
			for (unsigned int x = 0; x < sizeX; x++)
			{
				switch (map[y][x])
				{
				case 'A':
					type[writecount] = Type::Allies;
					//box[writecount] = Box::None;
					break;
				case 'E':
					type[writecount] = Type::Enemy;
					//box[writecount] = Box::None;
					break;
				case '.':
					type[writecount] = Type::Plain;
					//box[writecount] = Box::None;
					break;
				case 'M':
					type[writecount] = Type::Mountain;
					//box[writecount] = Box::None;
					break;
				case 'F':
					type[writecount] = Type::Forest;
					//box[writecount] = Box::None;
					break;
				case 'L':
				case 'C':
				case 0x0D:
				case 0x0A:
					break;
				default:
					type[writecount] = Type::None;
					//box[writecount] = Box::None;
					break;
				}
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
		//for (unsigned int i = 0; i < sizeY*sizeX; i++)
		//{
		//	output[i + 2 + sizeX * sizeY] = (char)box[i];
		//}

		fwrite(output, sizeof(char), 2 + (sizeX*sizeY), file);

		fclose(file);

		delete[] output;
	}

}
