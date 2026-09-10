use std::{collections::HashMap, path::PathBuf, time::Duration};

use uuid::Uuid;

#[derive(Debug)]
pub struct Metadata {
    pub path: String,
    pub title: String,
    pub track_no: u32,
    pub disc_no: u32,
    pub artist: String,
    pub album: String,
    pub album_artist: String,
    pub _release_date: String,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub struct SongId(Uuid);

#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub struct AlbumId {
    pub album_artist: ArtistNameAsId,
    pub title: String,
}

#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub struct ArtistNameAsId(pub String);

#[derive(Debug)]
pub struct Song {
    // File
    pub _path: PathBuf,

    // Metadata
    pub title: String,
    pub track_no: u16,
    pub disc_no: u16,

    // Relationships
    pub _artist: ArtistNameAsId,
    pub _album: AlbumId,

    // Technical information
    pub _duration: Option<Duration>,
}

#[derive(Debug)]
pub struct Album {
    pub title: String,
    pub _album_artist: ArtistNameAsId,
    pub year: Option<u16>,

    pub songs: Vec<SongId>,
}

impl Album {
    pub fn new(title: String, album_artist: String, year: Option<u16>) -> Album {
        Album {
            title,
            _album_artist: ArtistNameAsId(album_artist),
            year,
            songs: Vec::new(),
        }
    }

    pub fn add_song(&mut self, song_id: SongId) {
        self.songs.push(song_id);
    }
}

#[derive(Debug)]
pub struct Artist {
    pub _id: ArtistNameAsId,
}

impl Artist {
    pub fn new(name: String) -> Artist {
        Artist {
            _id: ArtistNameAsId(name),
        }
    }
}

#[derive(Debug, Default)]
pub struct Library {
    pub songs: HashMap<SongId, Song>,
    pub albums: HashMap<AlbumId, Album>,
    pub artists: HashMap<ArtistNameAsId, Artist>,
}

impl Library {
    pub fn new() -> Self {
        Library {
            songs: HashMap::new(),
            albums: HashMap::new(),
            artists: HashMap::new(),
        }
    }
}

pub fn populate_fields(lib: &mut Library, metadata_list: &Vec<Metadata>) {
    for elem in metadata_list {
        let song_id = SongId(Uuid::now_v7());
        let artist_id = ArtistNameAsId(elem.album_artist.clone());
        let album_id = AlbumId {
            album_artist: artist_id.clone(),
            title: elem.album.clone(),
        };

        let year = Some(0000); // to be replaced with year extracted from release date field

        lib.artists
            .entry(artist_id.clone())
            .or_insert_with(|| Artist::new(artist_id.0.clone()));

        let album = lib
            .albums
            .entry(album_id.clone())
            .or_insert_with(|| Album::new(elem.album.clone(), artist_id.0.clone(), year));

        let song = Song {
            _path: PathBuf::from(&elem.path),
            title: elem.title.clone(),
            track_no: elem.track_no as u16,
            disc_no: elem.disc_no as u16,
            _artist: ArtistNameAsId(elem.artist.clone()),
            _album: album_id,
            _duration: None,
        };

        lib.songs.insert(song_id, song);
        album.add_song(song_id);
    }

    for (i, (_song_id, song)) in lib.songs.iter().enumerate() {
        if i == 10 {
            break;
        }
        println!(
            "Song: {}, #track: {}, #disc: {}",
            song.title, song.track_no, song.disc_no
        );
    }

    for (i, (_album_id, album)) in lib.albums.iter().enumerate() {
        if i == 10 {
            break;
        }
        println!("Album: {}, Year: {:?}", album.title, album.year);
    }
}
