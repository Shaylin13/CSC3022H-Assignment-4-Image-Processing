#ifndef IMAGE_H
#define IMAGE_H
#include <memory>
#include <string>

namespace PDYSHA009 {
	
	class Image {

		friend std::ostream& operator<<(std::ostream& os, const Image& image);
		friend std::istream& operator>>(std::istream& is, Image& image);

		public:
			int height, width;
			std::unique_ptr<unsigned char[]> data;

			Image();
			Image(std::unique_ptr<unsigned char[]> data, int width, int height);
			Image(const Image& rhs);
			Image& operator=(const Image & rhs);
			Image(Image&& other);
			Image& operator=(Image&& rhs);

			~Image();

			Image operator+(const Image& rhs) const;

			Image operator-(const Image& rhs) const;

			Image operator!() const;

			Image operator/(const Image& rhs) const;

			Image operator*(const int threshold) const;

			void load(std::string fileName);
			void save(std::string fileName);

			class iterator {

				friend class Image;

				private:
					unsigned char *ptr;
					iterator(unsigned char *p) : ptr(p) {

					}

				public:
					iterator(const iterator& rhs) : ptr(rhs.ptr) {

					}

					const iterator operator++(int);
					
					const iterator& operator++();

					const iterator operator--(int);
					
					const iterator& operator--();

					unsigned char& operator*();

					iterator& operator=(iterator&& rhs);
					iterator& operator=(const iterator& rhs);

                    bool operator!=(const iterator& rhs);
					bool operator==(const iterator& rhs);
					
			};

			iterator begin(void) const;
			iterator end() const;

	};

	std::ostream& operator<<(std::ostream& os, const Image& image);
	std::istream& operator>>(std::istream& is, Image& image);
}

#endif
