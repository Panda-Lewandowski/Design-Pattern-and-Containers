#ifndef PROXY_HPP
#define PROXY_HPP
class Image {
    protected:
        int myId;
        Image() =default;
        ~Image() =default;
        virtual void draw() = 0;
};

class RealImage : public Image {
    public:
        RealImage(int i) { myId = i; }

        void draw() { cout << " drawing image " << myId << '\n'; }
};

class ProxyImage : public Image {
        RealImage* realImage;
        static int next;
    public:
        ProxyImage() {
            myId = next++;
            realImage = 0;
        }

        void draw() {
            if (!realImage) {
                realImage = new RealImage(myId);
            }
            realImage->draw();
        }
};

int ProxyImage::next = 1;

#endif // PROXY_HPP
