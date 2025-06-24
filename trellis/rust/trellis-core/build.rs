use std::env;
use std::path::PathBuf;

fn main() {
    let crate_dir = env::var("CARGO_MANIFEST_DIR").unwrap();

    // Absolute path to the proto root
    let proto_root = PathBuf::from(&crate_dir).join("../../../"); // <-- this resolves to trellis/

    let proto_files = [
        "trellis/core/discovery/pb/layer.proto",
        "trellis/core/discovery/pb/process.proto",
        "trellis/core/discovery/pb/sample.proto",
        "trellis/core/discovery/pb/service.proto",
        "trellis/core/discovery/pb/topic.proto",
    ]
    .iter()
    .map(|f| proto_root.join(f))
    .collect::<Vec<_>>();

    let include_paths = &[proto_root.clone()];

    prost_build::compile_protos(&proto_files, include_paths).unwrap();
}
