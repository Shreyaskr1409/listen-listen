use std::{collections::HashMap, path::PathBuf, time::Duration};

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub struct SongId(pub usize);

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub struct AlbumId(pub usize);

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub struct ArtistId(pub usize);

#[derive(Debug)]
pub struct Song {
    pub id: SongId,

    // File
    pub path: PathBuf,

    // Metadata
    pub title: String,
    pub track_no: u16,
    pub disc_no: u16,
    pub year: Option<u16>,

    // Relationships
    pub artist: ArtistId,
    pub album: AlbumId,

    // Technical information
    pub duration: Option<Duration>,
}

#[derive(Debug)]
pub struct Album {
    pub id: AlbumId,

    pub title: String,
    pub album_artist: ArtistId,
    pub year: Option<u16>,

    pub songs: Vec<SongId>,
}

#[derive(Debug)]
pub struct Artist {
    pub id: ArtistId,
    pub name: String,
}

pub struct Library {
    pub songs: HashMap<SongId, Song>,
    pub albums: HashMap<AlbumId, Album>,
    pub artists: HashMap<ArtistId, Artist>,
}
