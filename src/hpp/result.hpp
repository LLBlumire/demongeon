#ifndef INCL_RESULT_HPP
#define INCL_RESULT_HPP
namespace result {
    template <typename T,typename E>
    class Result {
        public:
            virtual bool is_ok() const = 0;
            virtual bool is_err() const = 0;
            virtual bool let_ok(T*& _0) = 0;
            virtual bool let_err(E*& _0) = 0;
            virtual ~Result() {}
    };
    template <typename T,typename E>
    class Ok : public Result<T,E> {
        public:
            bool is_ok() const {
                return true;
            }
            bool is_err() const {
                return false;
            }
            bool let_ok(T*& _0) {
                _0 = &this->_0;
                return true;
            }
            bool let_err(E*& _0) {
                return false;
            }
            Ok(T _0) {
                this->_0 = _0;
            }
        protected:
            T _0;
    };
    template <typename T,typename E>
    class Err : public Result<T,E> {
        public:
            bool is_ok() const {
                return false;
            }
            bool is_err() const {
                return true;
            }
            bool let_ok(T*& _0) {
                return false;
            }
            bool let_err(E*& _0) {
                _0 = &this->_0;
                return true;
            }
            Err(E _0) {
                this->_0 = _0;
            }
        protected:
            E _0;
    };
}
#endif
