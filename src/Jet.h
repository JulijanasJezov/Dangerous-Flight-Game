#include "DisplayableObject.h"
#include "Image.h"

class Jet :
	public DisplayableObject
{
public:
	Jet(BaseEngine* pEngine);
	~Jet();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void ChangeJet(int posX, int posY, int jet, bool bg);
	unsigned int GetColourPixel(int x, int y);
private:
	Image *jet;

protected:
	double m_dX;
	double m_dY;
	double m_dSX;
	double m_dSY;
};
