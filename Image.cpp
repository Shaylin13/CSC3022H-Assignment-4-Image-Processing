#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include "Image.h"

using namespace std;

namespace PDYSHA009 
{
	
			}
			else if (number < 0) {
				number = 0;
			}

			*inStart = (unsigned char)(number);

			++beg;
			++inStart;
		}

		return tmp;
	}

	Image Image::operator/(const Image& rhs) const
	{
		if(height == rhs.height && width == rhs.width)
		{
			Image tmp(rhs);

			Image::iterator beg = begin();
			Image::iterator inStart = tmp.begin();

			while (beg != end()) {
				if ((int)(*inStart) == 255) {
					int number = (int)(*beg);

					if (number > 255) {
						number = 255;
					}
					else if (number < 0) {
						number = 0;
					}

					*inStart = (unsigned char)(number);
				}

				++beg;
				++inStart;
			}

			return tmp;
		}

		else {
			exit(1);
		}
	}

	Image Image::operator*(const int threshold) const
	{
		Image tmp(*this);

		Image::iterator beg = begin();
		Image::iterator inStart = tmp.begin();

		while (beg != end()) {
			if ((int)(*inStart) <= threshold) {
				*inStart = (unsigned char)0;
			}
			else {
				*inStart = (unsigned char)255;
			}

			++beg;
			++inStart;
		}

		return tmp;
	}

	void Image::save(string saveFile) {
		ofstream file(saveFile, ios::out | ios::binary);

		file << "P5" << endl;
		file << "#" << saveFile << endl;
		file << width << " " << height << endl;
		file << "255" << endl;

		file.write((char*)data.get(), width*height);
		file.close();
	}

	void Image::load(string loadFile) {
		ifstream file(loadFile, ios::in | ios::binary);
		fileName = loadFile;

		string line;

		while (!file.eof()) {
			getline(file, line);

			if (line[0] == '#' || line == "P5") {
				continue;
			}

			else if (line == "255") {
				break;
			}

			else {
				stringstream ss(line);
				string number;

				getline(ss, number, ' ');
				width = stoi(number);

				getline(ss, number, ' ');
				height = stoi(number);
			}
		}

		unsigned char *imgbytes = new unsigned char[width*height];
		file.read((char*) imgbytes, width*height);
		file.close();

		data = unique_ptr<unsigned char[]>(imgbytes);
	}

	const Image::iterator& Image::iterator::operator++()
	{
		ptr ++;
		return *this;
	}

	const Image::iterator Image::iterator::operator++(int) {
		Image::iterator temp(*this);
		++ptr;
		return temp;
	}

	const Image::iterator& Image::iterator::operator--()
	{
		ptr --;
		return *this;
	}

	const Image::iterator Image::iterator::operator--(int) {
		Image::iterator temp(*this);
		--ptr;
		return temp;
	}

	unsigned char& Image::iterator::operator*() {
		return *ptr;
	}

	Image::iterator& Image::iterator::operator=(const Image::iterator& rhs)
	{
		ptr = rhs.ptr;
		return *this;
	}

	Image::iterator& Image::iterator::operator=(Image::iterator&& rhs)
	{
		ptr = rhs.ptr;
		rhs.ptr = nullptr;    
		return *this;
	}

	bool Image::iterator::operator==(const Image::iterator& rhs) {
		return (ptr == rhs.ptr);
	}

	bool Image::iterator::operator!=(const Image::iterator& rhs) {
		return (ptr != rhs.ptr);
	}

	Image::iterator Image::begin(void) const {
		return iterator(data.get());
	}

	Image::iterator Image::end() const {
		return iterator(&data[width*height]);
	}

	ofstream& operator<<(ofstream& os, const Image& image) {
		os << "P5" << "#" << image.width << " " << image.height << '\n' << 255 << endl;
		os.write((char*)image.data.get(), image.width*image.height);

		return os;
	}

	istream& operator>>(istream& is, Image& image) {
		string line;
		getline(is, line);

		while (line[0] == '#') {
			getline(is, line);
		}

		istringstream wh(line);
		wh >> image.width >> image.height;

		int values;
		is >> values >> ws;

		image.data = unique_ptr<unsigned char[]>(new unsigned char[image.width*image.height]);
		is.read((char*)image.data.get(), image.width*image.height);
		return is;
	}
}
