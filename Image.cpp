#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include "Image.h"

using namespace std;

namespace PDYSHA009 
{
	Image::Image() {
	//default constructor

		height = 0;
		width = 0;
		data = nullptr;
	}

	Image::Image(unique_ptr<unsigned char[]> inData, int inWidth, int inHeight) {
		width = inWidth;
		height = inHeight;
		data = move(inData);
	}

	Image::Image(const Image& rhs)
	//copy constructor
	{
		width = rhs.width;
		height = rhs.height;
    	data = unique_ptr<unsigned char[]>(new unsigned char[rhs.height * rhs.width]);

		Image::iterator beg = begin();
		Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

		while (inStart != inEnd) {
			*beg = *inStart;

			++beg;
			++inStart;
		}

	}

	Image& Image::operator=(const Image& rhs)
	{
		width = rhs.width;
		height = rhs.height;
    	data = unique_ptr<unsigned char[]>(new unsigned char[rhs.height * rhs.width]);

		Image::iterator beg = begin();
		Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

		while (inStart != inEnd) {
			*beg = *inStart;

			++beg;
			++inStart;
		}
		return *this;
	}

	Image::Image(Image&& rhs)
	{
		width = rhs.width;
		height = rhs.height;
        data = unique_ptr<unsigned char[]>(new unsigned char[rhs.height * rhs.width]);

		Image::iterator beg = begin();
		Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

		while (inStart != inEnd) {
			*beg = *inStart;

			++beg;
			++inStart;
		}

		rhs.width = 0;
		rhs.height = 0;
		rhs.data = nullptr;
	}

	Image& Image::operator=(Image&& rhs)
	{
		width = rhs.width;
		height = rhs.height;
		data = unique_ptr<unsigned char[]>(new unsigned char[rhs.height * rhs.width]);

		Image::iterator beg = begin();
		Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

		while (inStart != inEnd) {
			*beg = *inStart;

			++beg;
			++inStart;
		}

		rhs.width = 0;
		rhs.height = 0;
		rhs.data = nullptr;

		return *this;
	}

	Image::~Image() {

	}

	Image Image::operator+(const Image& rhs) const
	{
		if(height == rhs.height && width == rhs.width)
		{
			Image temp(*this);

			Image::iterator beg = temp.begin();
			Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

			while (inStart != inEnd) {
				int number = (int)(*beg) + (int)(*inStart);
				if (number > 255) {
					number = 255;
				}
				else if (number < 0) {
					number = 0;
				}

				*beg = (unsigned char)(number);

				++beg;
				++inStart;
			}

			return temp;
		}
		else {
			cout<<"Cannot add, dimensions of 2 images are not the same"<<endl;
		}
	}

	Image Image::operator-(const Image& rhs) const
	{
		if(height == rhs.height && width == rhs.width)
		{
			Image temp(*this);

			Image::iterator beg = temp.begin();
			Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

			while (inStart != inEnd) {
				int number = (int)(*beg) - (int)(*inStart);
				if (number > 255) {
					number = 255;
				}
				else if (number < 0) {
					number = 0;
				}

				*beg = (unsigned char)(number);

				++beg;
				++inStart;
			}

			return temp;
		}
		else {
			cout<<"Cannot subtract, dimensions of 2 images are not the same"<<endl;
		}
	}

	Image Image::operator!() const
	{
		Image temp(*this);

		Image::iterator beg = begin(), thisend = this->end();
		Image::iterator inStart = temp.begin();

		while (beg != thisend) {
			int number = 255 - (int)(*beg);

			if (number > 255) {
				number = 255;
			}
			else if (number < 0) {
				number = 0;
			}

			*inStart = (unsigned char)(number);

			++beg;
			++inStart;
		}

		return temp;
	}

	Image Image::operator/(const Image& rhs) const
	{
		if(height == rhs.height && width == rhs.width)
		{
			Image temp(rhs);

			Image::iterator beg = begin(), thisEnd = this->end();
			Image::iterator inStart = temp.begin();

			while (beg != thisEnd) {
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

			return temp;
		}

		else {
			cout<<"error, dimensions must be the same"<<endl;
		}
	}

	Image Image::operator*(const int threshold) const
	{
		Image temp(*this);

		Image::iterator beg = begin(), thisEnd = this->end();
		Image::iterator inStart = temp.begin();

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

		return temp;
	}

	void Image::save(string FileName) {
		ofstream file(FileName, ios::out | ios::binary);

		file << "P5" << endl;
		file << "#" << FileName << endl;
		file << width << " " << height << endl;
		file << "255" << endl;

		file.write((char*)data.get(), width*height);
		file.close();
	}

	void Image::load(string FileName) {
		ifstream inFile(FileName, ios::in | ios::binary);

		string line;

		while (!inFile.eof()) {
			getline(inFile, line);

			if (line[0] == '#' || line == "P5") {
				continue;
			}

			else if (line == "255") {
				break;
			}

			else {
				stringstream ss(line);
				string dimension;

				getline(ss, dimension, ' ');
				width = stoi(dimension);

				getline(ss, dimension, ' ');
				height = stoi(dimension);
			}
		}

		unsigned char *tempData = new unsigned char[width*height];
		inFile.read((char*) tempData, width*height);
		inFile.close();

		data = unique_ptr<unsigned char[]>(tempData);
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
		//return iterator(&data.get()+width*height);
	}

	ofstream& operator<<(ofstream& ostream, const Image& image) {
		ostream << "P5" << "#" << image.width << " " << image.height << '\n' << 255 << endl;
		ostream.write((char*)image.data.get(), image.width*image.height);

		return ostream;
	}

	istream& operator>>(istream& istream, Image& image) {
		string line;
		getline(istream, line);

		while (line[0] == '#') {
			getline(istream, line);
		}

		istringstream dimensions(line);
		dimensions >> image.width >> image.height;

		int values;
		istream >> values >> ws;

		image.data = unique_ptr<unsigned char[]>(new unsigned char[image.width*image.height]);
		istream.read((char*)image.data.get(), image.width*image.height);
		return istream;
	}
}
