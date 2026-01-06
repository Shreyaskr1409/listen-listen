use iced::{
    Alignment, Element, Length,
    widget::{Space, column, container, row, text},
};

use crate::{Message, component::button::custom_button};

pub fn player_controls() -> Element<'static, Message> {
    row![
        container(Space::new().height(150).width(150)).style(container::rounded_box),
        column![
            column![
                text("Postpostpartum").size(16),
                text("Injury Reserve").size(12),
                text("By the Time I Get to Phoenix").size(12),
            ]
            .spacing(4),
            Space::new().height(Length::Fill),
            row![
                custom_button("\u{23EE}", 25.0, 25.0, 20.0),
                custom_button("\u{25B6}", 25.0, 25.0, 16.0),
                custom_button("\u{23ED}", 25.0, 25.0, 20.0),
            ]
            .spacing(4)
        ]
        .spacing(4)
    ]
    .spacing(8)
    .align_y(Alignment::Center)
    .height(Length::Shrink)
    .into()
}
