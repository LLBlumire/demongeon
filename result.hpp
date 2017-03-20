#ifndef INCL_RESULT_HPP
#define INCL_RESULT_HPP

namespace result {
    template <typename T, typename E>
    class Result {
        public:
            virtual bool is_ok() const = 0;
            virtual bool is_err() const = 0;
            virtual bool unwrap_ok(T* t) const = 0;
            virtual bool unwrap_err(E* e) const = 0;
    };

    template <typename T, typename E>
    class Ok : public Result<T, E> {
        public:
            bool is_ok() const {
                return true;
            }
            bool is_err() const {
                return false;
            }
            bool unwrap_ok(T* t) const {
                *t = this->inner;
                return true;
            }
            bool unwrap_err(E* e) const {
                return false;
            }

            Ok(T inner) {
                this->inner = inner;
            }

        protected:
            T inner;
    };

    template <typename T, typename E>
    class Err : public Result<T, E> {
        public:
            bool is_ok() const {
                return false;
            }
            bool is_err() const {
                return true;
            }
            bool unwrap_ok(T* t) const {
                return false;
            }
            bool unwrap_err(E* e) const {
                *e = this->inner;
                return true;
            }

            Err(E inner) {
                this->inner = inner;
            }

        protected:
            E inner;
    };
}

#endif
