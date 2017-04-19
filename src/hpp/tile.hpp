#ifndef INCL_TILE_HPP
#define INCL_TILE_HPP

#include "item.hpp"
#include "enemy.hpp"
#include "coord.hpp"

namespace demon {
    namespace tile {
        typedef demon::Item ItemT;
        typedef demon::Enemy EnemyT;

        class Tile {
            public:
                virtual bool is_empty() const = 0;
                virtual bool is_item() const = 0;
                virtual bool is_enemy() const = 0;
                virtual bool is_player() const = 0;
                virtual bool let_empty() = 0;
                virtual bool let_item(ItemT*& _0) = 0;
                virtual bool let_enemy(EnemyT*& _0) = 0;
                virtual bool let_player() = 0;
                virtual char render() = 0;
                virtual ~Tile() {};
        };
        class Empty : public Tile {
            public:
                bool is_empty() const {
                    return true;
                }
                bool is_item() const {
                    return false;
                }
                bool is_enemy() const {
                    return false;
                }
                bool is_player() const {
                    return false;
                }
                bool let_empty() {
                    return true;
                }
                bool let_item(ItemT*& _0) {
                    return false;
                }
                bool let_enemy(EnemyT*& _0) {
                    return false;
                }
                bool let_player() {
                    return false;
                }
                char render() {
                    return ' ';
                }
                Empty() {
                }
            protected:
        };
        class Item : public Tile {
            public:
                bool is_empty() const {
                    return false;
                }
                bool is_item() const {
                    return true;
                }
                bool is_enemy() const {
                    return false;
                }
                bool is_player() const {
                    return false;
                }
                bool let_empty() {
                    return false;
                }
                bool let_item(ItemT*& _0) {
                    _0 = &this->_0;
                    return true;
                }
                bool let_enemy(EnemyT*& _0) {
                    return false;
                }
                bool let_player() {
                    return false;
                }
                char render() {
                    return '#';
                }
                Item(ItemT _0) {
                    this->_0 = _0;
                }
            protected:
                ItemT _0;
        };
        class Enemy : public Tile {
            public:
                bool is_empty() const {
                    return false;
                }
                bool is_item() const {
                    return false;
                }
                bool is_enemy() const {
                    return true;
                }
                bool is_player() const {
                    return false;
                }
                bool let_empty() {
                    return false;
                }
                bool let_item(ItemT*& _0) {
                    return false;
                }
                bool let_enemy(EnemyT*& _0) {
                    _0 = &this->_0;
                    return true;
                }
                bool let_player() {
                    return false;
                }
                char render() {
                    return this->_0.symbol;
                }
                Enemy(EnemyT _0) {
                    this->_0 = _0;
                }
            protected:
                EnemyT _0;
        };
        class Player : public Tile {
            public:
                bool is_empty() const {
                    return false;
                }
                bool is_item() const {
                    return false;
                }
                bool is_enemy() const {
                    return false;
                }
                bool is_player() const {
                    return true;
                }
                bool let_empty() {
                    return false;
                }
                bool let_item(ItemT*& _0) {
                    return false;
                }
                bool let_enemy(EnemyT*& _0) {
                    return false;
                }
                bool let_player() {
                    return true;
                }
                char render() {
                    return '@';
                }
                Player() {
                }
            protected:
        };
    }
}
#endif
