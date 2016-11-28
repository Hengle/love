/**
 * Copyright (c) 2006-2016 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

#ifndef LOVE_IMAGE_COMPRESSED_IMAGE_DATA_H
#define LOVE_IMAGE_COMPRESSED_IMAGE_DATA_H

// LOVE
#include "common/Data.h"
#include "common/StringMap.h"
#include "common/int.h"
#include "common/pixelformat.h"

// STL
#include <vector>

namespace love
{
namespace image
{

/**
 * CompressedImageData represents image data which is designed to be uploaded to
 * the GPU and rendered in its compressed form, without being decompressed.
 * http://renderingpipeline.com/2012/07/texture-compression/
 **/
class CompressedImageData : public Data
{
public:

	// Compressed image data can have multiple mipmap levels, each represented
	// by a sub-image.
	struct SubImage
	{
		int width, height;
		size_t size;
		uint8 *data; // Should not have ownership of the data.
	};

	CompressedImageData();
	virtual ~CompressedImageData();

	// Implements Data.
	virtual void *getData() const;
	virtual size_t getSize() const;

	/**
	 * Gets the number of mipmaps in this Compressed Image Data.
	 * Includes the base image level.
	 **/
	int getMipmapCount() const;

	/**
	 * Gets the size in bytes of a sub-image at the specified mipmap level.
	 **/
	size_t getSize(int miplevel) const;

	/**
	 * Gets the byte data of a sub-image at the specified mipmap level.
	 **/
	void *getData(int miplevel) const;

	/**
	 * Gets the width of a sub-image at the specified mipmap level.
	 **/
	int getWidth(int miplevel = 0) const;

	/**
	 * Gets the height of a sub-image at the specified mipmap level.
	 **/
	int getHeight(int miplevel = 0) const;

	/**
	 * Gets the format of the compressed data.
	 **/
	PixelFormat getFormat() const;

	bool isSRGB() const;

protected:

	PixelFormat format;

	bool sRGB;

	// Single block of memory containing all of the sub-images.
	uint8 *data;
	size_t dataSize;

	// Texture info for each mipmap level.
	std::vector<SubImage> dataImages;

	void checkMipmapLevelExists(int miplevel) const;

}; // CompressedImageData

} // image
} // love

#endif // LOVE_IMAGE_COMPRESSED_IMAGE_DATA_H
