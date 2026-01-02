use iced::{font};

pub struct FontConfig {
    pub default_font_family: &'static str,
}

pub const ZED_MONO_REGULAR_BYTES: &[u8] = include_bytes!("./assets/fonts/ZedMono/ZedMonoNerdFont-Regular.ttf");

fn load_fonts() {
    _ = font::load(ZED_MONO_REGULAR_BYTES);
}

pub fn setup_fonts() -> FontConfig {
    load_fonts();
    FontConfig { default_font_family: "ZedMono NF" }
}
