#ifndef FRAMERATEOPTIONS_H
#define FRAMERATEOPTIONS_H

#include <QString>
#include <QColor>
#include <QFont>
#include <memory>

class FramerateModel; // forward
class ResolutionsModel; // forward

// simple container for a color pick item used in QML
struct ColorPickItem {
    QString _name;
    QString _tooltip;
    QColor  _color;

    QString name() const { return _name; }
    QString tooltip() const { return _tooltip; }
    QColor  color() const { return _color; }

    void setName(const QString &n) { _name = n; }
    void setTooltip(const QString &t) { _tooltip = t; }
    void setColor(const QString &c) { _color = QColor(c); }
};

// simple container for pixel-difference like settings
struct NumericOption {
    QString _name;
    QString _tooltip;
    unsigned int _value{0};
    bool _enabled{false};

    QString name() const { return _name; }
    QString tooltip() const { return _tooltip; }
    unsigned int value() const { return _value; }
    bool enabled() const { return _enabled; }

    void setName(const QString &n) { _name = n; }
    void setTooltip(const QString &t) { _tooltip = t; }
    void setValue(unsigned int v) { _value = v; }
    void setEnabled(bool e) { _enabled = e; }
};

// displayed text options container
struct DisplayedTextOption {
    QString _name;
    QString _tooltip;
    QString _value;
    QFont   _font;
    bool    _enabled{false};

    QString name() const { return _name; }
    QString tooltip() const { return _tooltip; }
    QString value() const { return _value; }
    QFont   font() const { return _font; }
    bool    enabled() const { return _enabled; }

    void setName(const QString &n) { _name = n; }
    void setTooltip(const QString &t) { _tooltip = t; }
    void setValue(const QString &v) { _value = v; }
    void setFont(const QFont &f) { _font = f; }
    void setEnabled(bool e) { _enabled = e; }
};

// relative position option (used for FPS text position)
struct RelativePositionOption {
    QString _name;
    QString _tooltip;
    double  _value{0.0};

    QString name() const { return _name; }
    QString tooltip() const { return _tooltip; }
    double  value() const { return _value; }
    void setValue(double v) { _value = v; }
};

// FramerateOptions aggregates the above and provides a minimal API used by the rest of the code
class FramerateOptions {
public:
    FramerateOptions() = default;
    FramerateOptions(int id, std::shared_ptr<FramerateModel> /*fm*/, std::shared_ptr<ResolutionsModel> /*rm")
    {
        Q_UNUSED(id);
        // initialize sensible defaults
        fps_plot_color._name = QString("plot_color_%1").arg(id);
        fps_plot_color._tooltip = QString("Color for FPS plot ") + QString::number(id);
        fps_plot_color._color = QColor("#00FF00");

        pixel_difference._name = QString("pixel_diff_%1").arg(id);
        pixel_difference._tooltip = QString("Pixel difference threshold for video ") + QString::number(id);
        pixel_difference._value = 0;
        pixel_difference._enabled = false;

        displayed_text._name = QString("fps_text_%1").arg(id);
        displayed_text._tooltip = QString("Displayed FPS text for video ") + QString::number(id);
        displayed_text._value = QString("FPS");
        displayed_text._font = QFont();
        displayed_text._enabled = true;

        displayed_text_fontsize_override = false;

        rel_fps_text_x_position._name = QString("fps_x_%1").arg(id);
        rel_fps_text_x_position._tooltip = QString("Relative X position for FPS text ") + QString::number(id);
        rel_fps_text_x_position._value = 0.02;

        rel_fps_text_y_position._name = QString("fps_y_%1").arg(id);
        rel_fps_text_y_position._tooltip = QString("Relative Y position for FPS text ") + QString::number(id);
        rel_fps_text_y_position._value = 0.05;

        enabled = false;
    }

    void revert_to_default()
    {
        // simple fallback: reset enabled and numeric values
        pixel_difference._value = 0;
        pixel_difference._enabled = false;
        displayed_text._value = QString("FPS");
        displayed_text._enabled = true;
        displayed_text_fontsize_override = false;
        rel_fps_text_x_position._value = 0.02;
        rel_fps_text_y_position._value = 0.05;
    }

    // members accessed by other code
    ColorPickItem fps_plot_color;
    NumericOption  pixel_difference;
    DisplayedTextOption displayed_text;
    bool enabled{false};
    bool displayed_text_fontsize_override{false};
    RelativePositionOption rel_fps_text_x_position;
    RelativePositionOption rel_fps_text_y_position;
};

#endif // FRAMERATEOPTIONS_H
