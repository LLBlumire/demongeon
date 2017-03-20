#ifndef INCL_OPTIONAL_HPP
#define INCL_OPTIONAL_HPP

namespace optional {
    template <typename T>
    class Option {
        public:
            virtual bool is_some() const = 0;
            virtual bool is_none() const = 0;
            virtual bool unwrap_some(T* t) const = 0;
    };

    template <typename T>
    class Some : public Option<T> {
        public:
            bool is_some() const {
                return true;
            }
            bool is_none() const {
                return false;
            }
            bool unwrap_some(T* t) const {
                *t = this->inner;
                return true;
            }
            Some(T inner) {
                this->inner = inner;
            }
        protected:
            T inner;
    };

    template <typename T>
    class None : public Option<T> {
        public:
            bool is_some() const {
                return false;
            }
            bool is_none() const {
                return true;
            }
            bool unwrap_some(T* t) const {
                return false;
            }
            None() {}
    };
}

#endif
