use iced::{
    Alignment, Element, Length,
    widget::{self, container, text},
};

use crate::Message;

pub fn custom_buttom(txt: &str, w: f32, h: f32, text_size: f32) -> Element<'static, Message> {
    widget::button(
        container(text(String::from(txt)).size(text_size))
            .width(Length::Fixed(w))
            .height(Length::Fixed(h))
            .align_x(Alignment::Center)
            .align_y(Alignment::Center),
    )
    .into()
}
