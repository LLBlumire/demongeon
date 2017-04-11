#ifndef INCL_OPTION_HPP
#define INCL_OPTION_HPP
namespace option {
    template <typename T>
    class Option {
        public:
            virtual bool is_some() const = 0;
            virtual bool is_none() const = 0;
            virtual bool let_some(T*& _0) = 0;
            virtual bool let_none() = 0;
            virtual ~Option() {}
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
            bool let_some(T*& _0) {
                _0 = &this->_0;
                return true;
            }
            bool let_none() {
                return false;
            }
            Some(T _0) {
                this->_0 = _0;
            }
        protected:
            T _0;
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
            bool let_some(T*& _0) {
                return false;
            }
            bool let_none() {
                return true;
            }
            None() {
            }
        protected:
    };
}
#endif
