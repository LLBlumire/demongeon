#![feature(box_syntax)]

#[macro_use]
extern crate serde_derive;
extern crate toml;

use std::env::args;
use std::fs::File;
use std::io::Read;

#[derive(Deserialize, Serialize, Debug)]
struct SourceFile {
    name: String,
    gentypes: Vec<String>,
    variant: Vec<Variant>,
}

#[derive(Deserialize, Serialize, Debug)]
struct Variant {
    name: String,
    fields: Vec<String>,
}

fn main() {
    let input = {
        let input_path = args().nth(1).unwrap();;
        let mut file = File::open(input_path).unwrap();
        let mut buffer = String::new();
        file.read_to_string(&mut buffer).unwrap();
        buffer
    };
    process(&input);
}

fn pad(d: u16) {
    print!("{}", {
        let mut string = String::new();
        for _ in 0..d {
            string.push_str("    ");
        }
        string
    });
}

fn header(s: &SourceFile, d: u16) {
    pad(d);
    println!("#ifndef INCL_{}_HPP", s.name.to_uppercase());
    pad(d);
    println!("#define INCL_{}_HPP", s.name.to_uppercase());
}

fn footer(_: &SourceFile, d: u16) {
    pad(d);
    println!("#endif");
}

fn namespacei(s: &SourceFile, d: u16) {
    pad(d);
    println!("namespace {} {{", s.name.to_lowercase());
}

fn namespaceo(_: &SourceFile, d: u16) {
    pad(d);
    println!("}}");
}

fn templateh(s: &SourceFile, d: u16) {
    if s.gentypes.len() > 0 {
        pad(d);
        print!("template <");
        for (i, t) in s.gentypes.iter().enumerate() {
            print!("typename {}", t);
            if i != s.gentypes.len() - 1 {
                print!(",");
            }
        }
        println!(">");
    }
}

fn sclass(s: &SourceFile, d: u16) {
    pad(d); 
    println!("class {} {{", s.name);
    pad(d+1);
    println!("public:");
    for v in s.variant.iter() {
        pad(d+2);
        println!("virtual bool is_{}() const = 0;", v.name.to_lowercase());
    }
    for v in s.variant.iter() {
        pad(d+2);
        print!("virtual bool let_{}(", v.name.to_lowercase());
        for (i, f) in v.fields.iter().enumerate() {
            print!("{}*& _{}", f, i);
            if i != v.fields.len() - 1 {
                print!(",");
            }
        }
        println!(") = 0;");
    }
    pad(d);
    println!("}};");
}

fn classes(s: &SourceFile, d: u16) {
    for (ci, c) in s.variant.iter().enumerate() {
        templateh(s, d);
        pad(d);
        print!("class {} : public {}", c.name, s.name);
        if s.gentypes.len() > 0 {
            print!("<");
            for (i, t) in s.gentypes.iter().enumerate() {
                print!("{}", t);
                if i != s.gentypes.len() - 1 {
                    print!(",");
                }
            }
            print!(">");
        }
        println!(" {{");

        pad(d+1);
        println!("public:");
        for (vi, v) in s.variant.iter().enumerate() {
            pad(d+2);
            println!("bool is_{}() const {{", v.name.to_lowercase());
            pad(d+3);
            println!("return {};", ci == vi);
            pad(d+2);
            println!("}}");
        }
        for (vi, v) in s.variant.iter().enumerate() {
            pad(d+2);
            print!("bool let_{}(", v.name.to_lowercase());
            for (i, f) in v.fields.iter().enumerate() {
                print!("{}*& _{}", f, i);
                if i != v.fields.len() - 1 {
                    print!(",");
                }
            }
            println!(") {{");
            if ci == vi {
                for (i, _) in v.fields.iter().enumerate() {
                    pad(d+3);
                    println!("_{} = &this->_{};", i, i);
                }
                pad(d+3);
                println!("return true;");
            } else {
                pad(d+3);
                println!("return false;");
            }
            pad(d+2);
            println!("}}");
        }

        pad(d+2);
        print!("{}(", c.name);
        for (i, f) in c.fields.iter().enumerate() {
            print!("{} _{}", f, i);
            if i != c.fields.len() - 1 {
                print!(",");
            }
        }
        println!(") {{");

        for (i, _) in c.fields.iter().enumerate() {
            pad(d+3);
            println!("this->_{} = _{};", i, i);
        }

        pad(d+2);
        println!("}}");

        pad(d+2);
        println!("virtual ~{}() {{}}", c.name);

        pad(d+1);
        println!("protected:");

        for (i, f) in c.fields.iter().enumerate() {
            pad(d+2);
           println!("{} _{};", f, i);
        }

        pad(d);
        println!("}};");
    }
}

fn process(input: &str) {
    let source: SourceFile = toml::from_str(input).unwrap();
    header(&source, 0);
    namespacei(&source, 0);
    templateh(&source, 1);
    sclass(&source, 1);
    classes(&source, 1);
    namespaceo(&source, 0);
    footer(&source, 0);
}
