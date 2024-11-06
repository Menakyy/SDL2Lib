#ifndef ABSTRACTCALLBACK
#define ABSTRACTCALLBACK

class AbstractCallback
{
public:
    virtual ~AbstractCallback();

    virtual void run(void* caller) = 0;
};

template <class T>
class Callback : public AbstractCallback
{
public:
    Callback(void (T::*function)(void*), T* object) : function(function), object(object) {}

    void run(void* caller) override { (object->*function)(caller); }

private:
    T* object;
    void (T::*function)(void*);
};



#endif /* ABSTRACTCALLBACK */
