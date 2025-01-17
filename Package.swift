// swift-tools-version:5.9
 
import PackageDescription

let package = Package(
    name: "SVProgressHUD",
    platforms: [
        .iOS(.v12), 
        .tvOS(.v12)
    ],
    products: [
        .library(
            name: "SVProgressHUD",
            targets: ["SVProgressHUD"]
        )
    ],
    targets: [
        .target(
            name: "SVProgressHUD",
            dependencies: [],
            path: "SVProgressHUD",
            exclude: ["SVProgressHUD-Prefix.pch", "PrivacyInfo.xcprivacy"],
            resources: [
                .copy("SVProgressHUD.bundle"),
                .copy("PrivacyInfo.xcprivacy")
            ],
            publicHeadersPath: "include"
        )
    ]
)

