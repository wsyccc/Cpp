class Shape{ // actually shapes with colours
    private:
        int colour_;
    public:
        // constructor + default colour
        explicit Shape(int colour = 0) : colour_(colour) {}
        // prototype: (abstract)
        virtual void draw(std::ostream&) const = 0; // pure virtual function:
                                                    // needs to be declared virtual, and you put = 0 at the end.
                                                    // PVF means that we dont need to provide and implemenation (it's optional).
        //virtual void (std::ostream&) const = 0;
}