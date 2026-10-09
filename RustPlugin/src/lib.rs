#[link(name = "RhythmGameUtilities", kind = "dylib")]
unsafe extern "C" {}

#[allow(non_upper_case_globals)]
#[allow(non_camel_case_types)]
#[allow(non_snake_case)]
pub mod ffi {
    include!("bindings.rs");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_common() {
        unsafe {
            let result = ffi::RhythmGameUtilities_Lerp(0.0, 10.0, 0.5);

            assert_eq!(result, 5.0);
        }
    }
}
