#include "TMXLoader.h"

TileMap* TMXLoader::tileMap = NULL;

TMXLoader::TMXLoader() {
	tileMap = NULL;
}

bool TMXLoader::VisitEnter  (const TiXmlDocument  &doc) {
	// TODO: for performance, we may not want to return true for each of these callbacks for the visitor pattern.
    return true; 
}

bool TMXLoader::VisitExit (const TiXmlDocument &doc) {
    return true;
}

bool TMXLoader::VisitEnter (const TiXmlElement &elem, const TiXmlAttribute *attrib) {

	if (tileMap == NULL) return false;

    if (string("map") == elem.Value()) {
        elem.Attribute("width", &tileMap->width);
        elem.Attribute("height", &tileMap->height);
		elem.Attribute("tilewidth", &tileMap->tileWidth);
        elem.Attribute("tileheight", &tileMap->tileHeight);

		tileMap->diagonalSize = (tileMap->width >= tileMap->height) ? tileMap->width : tileMap->height;
    }
    
	else if (string("tileset") == elem.Value()) {

		int tilewidth = 0;
		int tileheight = 0;
		int tilespacing = 0;
		int tilemargin = 0;
		int tilegid = 0;
		
        elem.Attribute("tilewidth", &tilewidth);
        elem.Attribute("tileheight", &tileheight);
        elem.Attribute("spacing", &tilespacing);
        elem.Attribute("margin", &tilemargin);
		elem.Attribute("firstgid", &tilegid);
		
		TileSet* tileSet = new TileSet(tilewidth, tileheight, tilespacing, tilemargin, tilegid);
		tileMap->tileSets.push_back(tileSet);
		
    }
	
    else if (string("image") == elem.Value()) {
		std::string attrib = StrUtils::getString(elem.Attribute("source"));

		if (tileMap->tileSets.size() > 0) {
			TileSet *t = tileMap->tileSets.back();
			t->loadImage(game::File::combinePath(tileMap->filePath, attrib));
		}
    }
    
	else if (string("layer") == elem.Value()) {
		int w = 0;
		int h = 0;
		TileLayer *tile;
		
        elem.Attribute("width", &w);
        elem.Attribute("height", &h);
		
		tile = new TileLayer(w, h);
		tileMap->tileLayers.push_back(tile);
		
    }
    
	else if (string("data") == elem.Value()) {
		if (tileMap->tileLayers.size() > 0) {
			
			std::string encoding = StrUtils::getString(elem.Attribute("encoding"));
			std::string compression = StrUtils::getString(elem.Attribute("compression"));
			std::string text = StrUtils::getString(elem.GetText());
			
			
			if (encoding.compare("base64") == 0) {
				
				if (compression.compare("zlib") == 0) {
					decodeMapData(text, COMPRESSION_ZLIB);
					
				}
				else if (compression.compare("") == 0) {
					// Uncompressed data
					decodeMapData(text, COMPRESSION_NONE);
				}
				
			}
			else {
				// Unsupport encoding
			}
			
			
		}    

	}

    return true;
}

bool TMXLoader::VisitExit (const TiXmlElement &elem) {
    return true;
}

bool TMXLoader::Visit (const TiXmlDeclaration &dec) {
    return true;
}

bool TMXLoader::Visit (const TiXmlText &text) {
    return true;
}

bool TMXLoader::Visit (const TiXmlComment &comment) {
    return true;
}

bool TMXLoader::Visit (const TiXmlUnknown &unknown) {
    return true;
}

TileMap* TMXLoader::loadMap(const char* filename)
{
	TMXLoader mapLoader;
	tileMap = new TileMap();

    TiXmlDocument doc(filename);
    if (doc.LoadFile()) {
		tileMap->filePath = game::File::getPath(filename);
		doc.Accept(&mapLoader);
	}
	else {
		cout << "Failed to load " << filename << "\n";
	}

	return tileMap;
}

void TMXLoader::decodeMapData(string encoded_data, TileDataCompression compression) {

	TileLayer *layer = tileMap->tileLayers.back();
	
	int layerWidth = layer->tileWidth;
	int layerHeight = layer->tileHeight;
		
    int m_LayerRow = 0;
    int m_LayerCol = 0;

	string unencoded_data;
	
	StrUtils::convertFromBase64(encoded_data, unencoded_data);
	
	int dataSize = unencoded_data.size();

    for (int i = 0; i < layerWidth; i++) {
		layer->tileData.push_back(vector<int>(layerHeight));
    }
	
	cout << "\ndatasize: " << dataSize << "\n";
	
    for (int i = 0; i < dataSize; i += 4)
    {
        // Get the grid ID
        int a = unencoded_data[i];
        int b = unencoded_data[i + 1];
        int c = unencoded_data[i + 2];
        int d = unencoded_data[i + 3];
		
        int gid = a | b << 8 | c << 16 | d << 24;
		layer->tileData[m_LayerRow][m_LayerCol] = gid;

        if ((i + 4) % ( tileMap->height * 4) == 0) {
            m_LayerRow++;
            m_LayerCol = 0;
			cout << "\n";
		}
        else {
            m_LayerCol++;
			cout << gid;
        }
    }

	
}


