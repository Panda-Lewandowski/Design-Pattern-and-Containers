#ifndef FACADE_HPP
#define FACADE_HPP

class Band {
    private:
        GuitarPlayer _GuitarPlayer;
        Drummer _Drummer;
        BassPlayer _BassPlayer;
        void PlayVerse(int nVerse);
        void PlayChorus();
        void PlaySolo();
    public:
        Band(const char *guitarPlayerName, const char *drummerName,
             const char *bassPlayerName) : _GuitarPlayer(guitarPlayerName),
            _Drummer(drummerName), _BassPlayer(bassPlayerName) { }
        ~Band() { }
        void PlaySong();
};

class Musician {
    protected:
        string _Name;
public:
    virtual ~Musician() { }
};

class GuitarPlayer: public Musician {
public:
    GuitarPlayer(const char *name) { _Name = name; }
    ~GuitarPlayer() override { }
    void PlayVerseRiff(int nVerse);
    void PlayChorusRiff();
    void PlaySolo();
};

#endif // FACADE_HPP
