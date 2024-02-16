//
//  SVProgressHUD.h
//  SVProgressHUD, https://github.com/SVProgressHUD/SVProgressHUD
//
//  Copyright (c) 2011-2023 Sam Vermette and contributors. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AvailabilityMacros.h>
#import "SVIndefiniteAnimatedView.h"
#import "SVProgressAnimatedView.h"
#import "SVRadialGradientLayer.h"

NS_ASSUME_NONNULL_BEGIN

extern NSNotificationName const SVProgressHUDDidReceiveTouchEventNotification;
extern NSNotificationName const SVProgressHUDDidTouchDownInsideNotification;
extern NSNotificationName const SVProgressHUDWillDisappearNotification;
extern NSNotificationName const SVProgressHUDDidDisappearNotification;
extern NSNotificationName const SVProgressHUDWillAppearNotification;
extern NSNotificationName const SVProgressHUDDidAppearNotification;

extern NSString * const SVProgressHUDStatusUserInfoKey;

/// Represents the appearance style of the HUD.
typedef NS_ENUM(NSInteger, SVProgressHUDStyle) {
    /// White HUD with black text. HUD background will be blurred.
    SVProgressHUDStyleLight,
    
    /// Black HUD with white text. HUD background will be blurred.
    SVProgressHUDStyleDark,
    
    /// Uses the fore- and background color properties.
    SVProgressHUDStyleCustom,
    
    /// Automatically switch between light or dark mode appearance.
    SVProgressHUDStyleAutomatic
};

/// Represents the type of mask to be applied when the HUD is displayed.
typedef NS_ENUM(NSUInteger, SVProgressHUDMaskType) {
    /// Allow user interactions while HUD is displayed.
    SVProgressHUDMaskTypeNone,
    
    /// Don't allow user interactions with background objects.
    SVProgressHUDMaskTypeClear,
    
    /// Don't allow user interactions and dim the UI behind the HUD (as in iOS 7+).
    SVProgressHUDMaskTypeBlack,
    
    /// Don't allow user interactions and dim the UI with an UIAlertView-like background gradient (as in iOS 6).
    SVProgressHUDMaskTypeGradient,
    
    /// Don't allow user interactions and dim the UI behind the HUD with a custom color.
    SVProgressHUDMaskTypeCustom
};

/// Represents the animation type of the HUD when it's shown or hidden.
typedef NS_ENUM(NSUInteger, SVProgressHUDAnimationType) {
    /// Custom flat animation (indefinite animated ring).
    SVProgressHUDAnimationTypeFlat,
    
    /// iOS native UIActivityIndicatorView.
    SVProgressHUDAnimationTypeNative
};

@interface SVProgressHUD : UIView

#pragma mark - Customization

/// Represents the default style for the HUD.
/// @discussion Default: SVProgressHUDStyleAutomatic.
@property (assign, nonatomic) SVProgressHUDStyle defaultStyle UI_APPEARANCE_SELECTOR;

/// Represents the type of mask applied when the HUD is displayed.
/// @discussion Default: SVProgressHUDMaskTypeNone.
@property (assign, nonatomic) SVProgressHUDMaskType defaultMaskType UI_APPEARANCE_SELECTOR;

/// Defines the animation type used when the HUD is displayed.
/// @discussion Default: SVProgressHUDAnimationTypeFlat.
@property (assign, nonatomic) SVProgressHUDAnimationType defaultAnimationType UI_APPEARANCE_SELECTOR;

/// The container view used for displaying the HUD. If nil, the default window level is used.
@property (strong, nonatomic, nullable) UIView *containerView;

/// The minimum size for the HUD. Useful for maintaining a consistent size when the message might cause resizing.
/// @discussion Default: CGSizeZero.
@property (assign, nonatomic) CGSize minimumSize UI_APPEARANCE_SELECTOR;

/// Thickness of the ring shown in the HUD.
/// @discussion Default: 2 pt.
@property (assign, nonatomic) CGFloat ringThickness UI_APPEARANCE_SELECTOR;

/// Radius of the ring shown in the HUD when there's associated text.
/// @discussion Default: 18 pt.
@property (assign, nonatomic) CGFloat ringRadius UI_APPEARANCE_SELECTOR;

/// Radius of the ring shown in the HUD when there's no associated text.
/// @discussion Default: 24 pt.
@property (assign, nonatomic) CGFloat ringNoTextRadius UI_APPEARANCE_SELECTOR;

/// Corner radius of the HUD view.
/// @discussion Default: 14 pt.
@property (assign, nonatomic) CGFloat cornerRadius UI_APPEARANCE_SELECTOR;

/// Font used for text within the HUD.
/// @discussion Default: [UIFont preferredFontForTextStyle:UIFontTextStyleSubheadline].
@property (strong, nonatomic) UIFont *font UI_APPEARANCE_SELECTOR;

/// Background color of the HUD.
/// @discussion Default: [UIColor whiteColor].
@property (strong, nonatomic) UIColor *backgroundColor UI_APPEARANCE_SELECTOR;

/// Foreground color used for content in the HUD.
/// @discussion Default: [UIColor blackColor].
@property (strong, nonatomic) UIColor *foregroundColor UI_APPEARANCE_SELECTOR;

/// Color for any foreground images in the HUD.
/// @discussion Default: same as foregroundColor.
@property (strong, nonatomic) UIColor *foregroundImageColor UI_APPEARANCE_SELECTOR;

/// Color for the background layer behind the HUD.
/// @discussion Default: [UIColor colorWithWhite:0 alpha:0.4].
@property (strong, nonatomic) UIColor *backgroundLayerColor UI_APPEARANCE_SELECTOR;

/// Size of any images displayed within the HUD.
/// @discussion Default: 28x28 pt.
@property (assign, nonatomic) CGSize imageViewSize UI_APPEARANCE_SELECTOR;

/// Indicates whether images within the HUD should be tinted.
/// @discussion Default: YES.
@property (assign, nonatomic) BOOL shouldTintImages UI_APPEARANCE_SELECTOR;

/// The image displayed when showing informational messages.
/// @discussion Default: info.circle from SF Symbols (iOS 13+) or the bundled info image provided by Freepik.
@property (strong, nonatomic) UIImage *infoImage UI_APPEARANCE_SELECTOR;

/// The image displayed when showing success messages.
/// @discussion Default: checkmark from SF Symbols (iOS 13+) or the bundled success image provided by Freepik.
@property (strong, nonatomic) UIImage *successImage UI_APPEARANCE_SELECTOR;

/// The image displayed when showing error messages.
/// @discussion Default: xmark from SF Symbols (iOS 13+) or the bundled error image provided by Freepik.
@property (strong, nonatomic) UIImage *errorImage UI_APPEARANCE_SELECTOR;

/// A specific view for extensions. This property is only used if #define SV_APP_EXTENSIONS is set.
/// @discussion Default: nil.
@property (strong, nonatomic) UIView *viewForExtension UI_APPEARANCE_SELECTOR;

/// The interval in seconds to wait before displaying the HUD. If the HUD is displayed before this time elapses, this timer is reset.
/// @discussion Default: 0 seconds.
@property (assign, nonatomic) NSTimeInterval graceTimeInterval;

/// The minimum amount of time in seconds the HUD will display.
/// @discussion Default: 5.0 seconds.
@property (assign, nonatomic) NSTimeInterval minimumDismissTimeInterval;

/// The maximum amount of time in seconds the HUD will display.
/// @discussion Default: DBL_MAX.
@property (assign, nonatomic) NSTimeInterval maximumDismissTimeInterval;

/// Offset from the center position, can be used to adjust the HUD position.
/// @discussion Default: 0, 0.
@property (assign, nonatomic) UIOffset offsetFromCenter UI_APPEARANCE_SELECTOR;

/// Duration of the fade-in animation when showing the HUD.
/// @discussion Default: 0.15.
@property (assign, nonatomic) NSTimeInterval fadeInAnimationDuration UI_APPEARANCE_SELECTOR;

/// Duration of the fade-out animation when hiding the HUD.
/// @discussion Default: 0.15.
@property (assign, nonatomic) NSTimeInterval fadeOutAnimationDuration UI_APPEARANCE_SELECTOR;

/// The maximum window level on which the HUD can be displayed.
/// @discussion Default: UIWindowLevelNormal.
@property (assign, nonatomic) UIWindowLevel maxSupportedWindowLevel;

/// Indicates if haptic feedback should be used.
/// @discussion Default: NO.
@property (assign, nonatomic) BOOL hapticsEnabled;

/// Indicates if motion effects should be applied to the HUD.
/// @discussion Default: YES.
@property (assign, nonatomic) BOOL motionEffectEnabled;

@property (class, strong, nonatomic, readonly) NSBundle *imageBundle;

@property (class, strong, nonatomic, readonly) SVProgressHUD *sharedProgressHUD;


#pragma mark - Show Methods

/// Shows the HUD without any additional status message.
+ (void)show;

/// Shows the HUD with a provided status message.
/// @param status The message to be displayed alongside the HUD.
+ (void)showWithStatus:(nullable NSString*)status;

/// Display methods to show progress on the HUD.

/// Shows the HUD with a progress indicator.
/// @param progress A float value between 0.0 and 1.0 indicating the progress.
+ (void)showProgress:(float)progress;

/// Shows the HUD with a progress indicator and a provided status message.
/// @param progress A float value between 0.0 and 1.0 indicating the progress.
/// @param status The message to be displayed alongside the progress indicator.
+ (void)showProgress:(float)progress status:(nullable NSString*)status;

/// Shows an info status with the provided message.
/// @param status The info message to be displayed.
+ (void)showInfoWithStatus:(nullable NSString*)status;

/// Shows a success status with the provided message.
/// @param status The success message to be displayed.
+ (void)showSuccessWithStatus:(nullable NSString*)status;

/// Shows an error status with the provided message.
/// @param status The error message to be displayed.
+ (void)showErrorWithStatus:(nullable NSString*)status;

/// Shows a custom image with the provided status message.
/// @param image The custom image to be displayed.
/// @param status The message to accompany the custom image.
+ (void)showImage:(UIImage*)image status:(nullable NSString*)status;

/// Decreases the activity count, dismissing the HUD if count reaches 0.
+ (void)popActivity;

/// Dismisses the HUD immediately.
+ (void)dismiss;

/// Dismisses the HUD and triggers a completion block.
/// @param completion A block that gets executed after the HUD is dismissed.
+ (void)dismissWithCompletion:(nullable void (^)(void))completion;

/// Dismisses the HUD after a specified delay.
/// @param delay The time in seconds after which the HUD should be dismissed.
+ (void)dismissWithDelay:(NSTimeInterval)delay;

/// Dismisses the HUD after a specified delay and triggers a completion block.
/// @param delay The time in seconds after which the HUD should be dismissed.
/// @param completion A block that gets executed after the HUD is dismissed.
+ (void)dismissWithDelay:(NSTimeInterval)delay completion:(nullable void (^)(void))completion;

/// Checks if the HUD is currently visible.
/// @return A boolean value indicating whether the HUD is visible.
+ (BOOL)isVisible;

/// Calculates the display duration based on a given string's length.
/// @param string The string whose length determines the display duration.
/// @return A time interval representing the display duration.
+ (NSTimeInterval)displayDurationForString:(nullable NSString*)string;

@end

NS_ASSUME_NONNULL_END
