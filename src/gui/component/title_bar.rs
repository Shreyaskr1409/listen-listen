use iced::{
    Element,
    widget::{button, row, space::horizontal, text},
};

use crate::Message;

pub fn title_bar() -> Element<'static, Message> {
    row![
        button("Home").on_press(Message::Default),
        text("Listen-Listen").size(24),
        horizontal(),
        button("-").on_press(Message::Minimize),
        button("=").on_press(Message::Maximize),
        button("X").on_press(Message::Exit),
    ]
    .spacing(4)
    .into()
}
