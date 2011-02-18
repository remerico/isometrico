#ifndef TMXLOADER_H
#define TMXLOADER_H


#include "SDL.h"
#include "SDL_image.h"

#include <iostream>
#include <string>
#include <vector>

#include "b64/decode.h"
#include "tinyxml/tinyxml.h"

#include "TileMap.h"
#include "TileSet.h"
#include "TileLayer.h"
#include "Utils/StrUtils.h"
#include "Core/File.h"

using namespace std;

enum TileDataCompression {
	COMPRESSION_NONE,
	COMPRESSION_GZIP,
	COMPRESSION_ZLIB
};

class TMXLoader : public TiXmlVisitor
{
public:
	TMXLoader();

	static TileMap* loadMap(const char* filename);

protected:

	virtual bool VisitEnter  (const TiXmlDocument  &);
	virtual bool VisitExit (const TiXmlDocument &);
	virtual bool VisitEnter (const TiXmlElement &, const TiXmlAttribute *);
	virtual bool VisitExit (const TiXmlElement &);
	virtual bool Visit (const TiXmlDeclaration &);
	virtual bool Visit (const TiXmlText &);
	virtual bool Visit (const TiXmlComment &);
	virtual bool Visit (const TiXmlUnknown &);

private:

	static TileMap *tileMap;
	
	void decodeMapData(string encoded_data, TileDataCompression compression = COMPRESSION_NONE);
	

};

#endif // TMXLOADER_H
