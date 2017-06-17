#ifndef BRIDGE_HPP
#define BRIDGE_HPP
class Window {
public:
    Window(View* contents);
    // запросы, обрабатываемые окном
    virtual void DrawContents();
    virtual void Open();
    virtual void Close();
    virtual void Iconify();
    virtual void Deiconify();

    // запросы, перенаправляемые реализации
    virtual void SetOrigin(const Point& at);
    virtual void SetExtent(const Point& extent);
    virtual void Raise();
    virtual void Lower();

    virtual void DrawLine(const Point&, const Point&);
    virtual void DrawRect(const Point&, const Point&);
    virtual void DrawPolygon(const Point[], int n);
    virtual void DrawText(const char*, const Point&);
protected:
    WindowImp* GetWindowImp();
    View* GetView();
private:
    WindowImp* _imp;
    View* _contents; // содержимое окна
};

class WindowImp {
public:
    virtual void ImpTop() = 0;
    virtual void ImpBottom() = 0;
    virtual void ImpSetExtent(const Point&) = 0;
    virtual void ImpSetOrigin(const Point&) = 0;
    virtual void DeviceRect(Coord, Coord, Coord, Coord) = 0;
    virtual void DeviceText(const char*, Coord, Coord) = 0;
    virtual void DeviceBitmap(const char*, Coord, Coord) = 0;
    //..
protected:
    WindowImp();
};

WindowImp* Window::GetWindowImp () {
    if (_imp == 0) {
        _imp = WindowSystemFactory::Instance()->MakeWindowImp();
    }
    return _imp;
}

class ApplicationWindow : public Window {
public:
// ...
    virtual void DrawContents();
};

void ApplicationWindow::DrawContents () {
        GetView()->DrawOn(this);
}
#endif // BRIDGE_HPP
