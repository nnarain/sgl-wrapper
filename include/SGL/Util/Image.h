
#ifndef IMAGE_H
#define IMAGE_H

#include <SGL/Util/SGLExport.h>

#include <SGL/GL/Texture.h>

#include <string>
#include <cstdint>

namespace sgl
{
	/**
		General Image Loader Class

		Loads Uncompressed Bitmaps, TGA
	*/
	SGLCLASS Image
	{
	private:
		Image(void);

	public:

		/* Types */

		//! Format
		enum class Format
		{
			BMP, TGA, PNG, DDS
		};

		// packing headers
		#pragma pack(push, 1)

		//! Bitmap Header
		struct BitmapHeader
		{
			char signature[2];             // should be 'BM'
			uint32_t size;                 // unreliable
			uint16_t reserved1;            // 0
			uint16_t reserved2;            // 0
			uint32_t dataOffset;           // offset to image data
			uint32_t bitmapHeaderInfoSize; // 40
			uint32_t width;                //
			uint32_t height;               //
			uint16_t numPlanes;            //
			uint16_t bitsPerPixel;         // 24 for RGB
			uint32_t compression;          // compression type - not supported
			uint32_t imageDataSize;        // size of image data
			uint32_t xRes;                 // horizontal image resolution
			uint32_t yRes;                 // vertical image resolution
			uint32_t numColors;            // number of colors
			uint32_t numImportantColors;   // number of important colors
		};

		// TGA Header
		struct TGAHeader
		{
			uint8_t  idLen;
			uint8_t  colorMapType;
			uint8_t  imageType;
			uint16_t cmapStart;
			uint16_t cmapLen;
			uint8_t  cmapDepth;
			uint16_t xoffset;
			uint16_t yoffset;
			uint16_t width;
			uint16_t height;
			uint8_t  pixelDepth;
			uint8_t  imageDescriptor;
		};

		struct DDSPixelFormat
		{
			uint32_t size;
			uint32_t flags;
			char     fourCC[4];
			uint32_t rgbBitCount;
			uint32_t rBitMask;
			uint32_t gBitMask;
			uint32_t bBitMask;
			uint32_t aBitMask;
		};

		struct DDSHeader
		{
			char           signature[4];
			uint32_t       size;
			uint32_t       flags;
			uint32_t       height;
			uint32_t       width;
			uint32_t       linearSize;
			uint32_t       depth;
			uint32_t       mipMapCount;
			uint32_t       reserved1[11];
			DDSPixelFormat ddspf;
			uint32_t       caps;
			uint32_t       caps2;
			uint32_t       caps3;
			uint32_t       caps4;
			uint32_t       reserved2;
		};

		#pragma pack(pop)

		/* Public Functions */

		static void load(Texture& texture, const char *filename);

	private:

		/* Private Functions */

		/**
			Load an uncompressed Bitmap file
		*/
		static void loadBMP(Texture& texture, const char *filename);

		/**
			Load an uncompressed TGA file
		*/
		static void loadTGA(Texture& texture, const char *filename);

		/**
			Load PNG file
		*/
		static void loadPNG(Texture& texture, const char *filename);

		/**
			Load DDS file
		*/
		static void loadDDS(Texture& texture, const char *filename);

		/**
			@return the file extension of the given file name
		*/
		static std::string getFileExtension(const std::string &filename);

		/**
			@return the Image::Format corresponding to the given extension string
		*/
		static Image::Format findFormat(const std::string &ext);

	};
}

#endif
