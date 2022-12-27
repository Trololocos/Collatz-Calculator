use std::collections::BTreeSet;

const PRINT: u128 = 2 << 24;
fn main() {
    let mut cache = BTreeSet::new();
    
    for i in 0..u128::MAX {
        if i % PRINT == 0 {
            //println!("{i}")
        };

        let mut num = i;
        loop {
            if num < i || !cache.insert(num) {break;}
            if num % 2 == 0 { num /= 2; }
            else { num = num * 3 + 1 }            
        }
        cache.remove(&i);
    }
}
