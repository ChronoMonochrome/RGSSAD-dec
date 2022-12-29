#include <iostream>
#include <BinaryReader.hpp>

using namespace rgssad;

using namespace std;

int main()
{
	BinaryReader br("Game.rgss2a");
	cout << br.readUint32() << endl;
	cout << br.read(10) << endl;
	return 0;
}
