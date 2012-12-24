/*
 * SafePointer.h
 *
 *  Created on: Dec 22, 2012
 *      Author: rulk
 */
#ifndef SAFEPOINTER_H
#define SAFEPOINTER_H
namespace StingRay
{
#include <list>
template <typename P> class SafePointerClient;
template<typename T> class SafePointer
{
    public:
        SafePointer(){pointer = NULL;}
        virtual bool isNULL()
        {
         if(pointer == NULL)
         return true;
         return false;
        }
        SafePointer(T * p)
        {
            pointer = NULL;
            setPointer(p);
        }
        virtual ~SafePointer()
        {
            setPointer(NULL);
        }
        T* operator ->() const
        {
           return getPointer();
        }

        T* getPointer() const
        {
            if(pointer != NULL)
                return pointer;
            else throw 10;
        }
        SafePointer(const FTSafePointer & copy)
        {
            pointer = NULL;
            setPointer(copy.pointer);

        }
        SafePointer & operator = (const FTSafePointer & copy)
        {
            setPointer(copy.pointer);
            return *this;
        }
        SafePointer & operator = ( T * copy)
        {
            setPointer(copy);
            return *this;
        }
        T & operator *() const
        {
            return getPointer();
        }
        friend class SafePointerClient<T>;
    protected:
        virtual void pointerNulled(const T * p )
        {
            if(pointer == p)
                pointer = NULL;

        }
        virtual void setPointer(T * p)
        {

            if(pointer != NULL)
                pointer->unRegisterPointer(this);
            if(p == NULL)
            {
                pointer = NULL;
                return;
            }
            if(p->registerPointer(this))
                pointer = p;
            else pointer = NULL;
        }

     private:
     T * pointer;
};
template <typename P> class SafePointerClient
{
      public:
      virtual ~SafePointerClient()
      {
           safepointerList.unique();
           typename std::list< FTSafePointer<P> *>::iterator it;
           it = safepointerList.begin();
           while(it != safepointerList.end())
           {
               (*it)->pointerNulled((P*)this);
               it++;
           }

      }
      friend class SafePointer< P>;
      private:
      bool registerPointer( SafePointer<P> * pointer)
      {
            safepointerList.push_back(pointer);
            return true;
      }
      void unRegisterPointer( SafePointer<P> * pointer )
      {
          safepointerList.remove(pointer);
      }
      std::list< SafePointer<P> *> safepointerList;
};
}
#endif // SAFEPOINTER_H
