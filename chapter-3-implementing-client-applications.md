# Implementing Client Applications

## Introduction

- Máy khách là một phần của ứng dụng phân tán giao tiếp với một phần khác của ứng dụng này được gọi là máy chủ, để sử dụng các dịch vụ mà nó cung cấp. Mặt khác, máy chủ là một phần của ứng dụng phân tán chờ đợi một cách thụ động các yêu cầu đến từ máy khách. Khi một yêu cầu đến, máy chủ thực hiện hoạt động được yêu cầu và gửi phản hồi - kết quả của hoạt động - trở lại máy khách.

- Đặc điểm chính của máy khách là nó cần một dịch vụ do máy chủ cung cấp và nó bắt đầu phiên giao tiếp với máy chủ đó để sử dụng dịch vụ. Đặc điểm chính của máy chủ là nó phục vụ các yêu cầu đến từ các máy khách bằng cách cung cấp một dịch vụ được yêu cầu.

### The classification of client applications

- Các ứng dụng máy khách có thể được phân loại theo giao thức lớp transport mà chúng sử dụng để giao tiếp với máy chủ. Nếu máy khách sử dụng giao thức UDP, nó được gọi là máy khách UDP. Nếu nó sử dụng giao thức TCP, nó được gọi là client TCP tương ứng. Tất nhiên, có nhiều giao thức lớp transport khác mà các ứng dụng khách có thể sử dụng để giao tiếp. Hơn nữa, có những ứng dụng khách đa giao thức có thể giao tiếp qua một số giao thức.

- Quyết định chọn giao thức lớp transport nào để giao tiếp giữa các phần của ứng dụng phân tán cần được thực hiện ở giai đoạn đầu của thiết kế ứng dụng dựa trên đặc điểm kỹ thuật của ứng dụng. Bởi vì các giao thức TCP và UDP khác nhau về mặt khái niệm, có thể khá khó khăn để chuyển từ một trong hai giao thức này sang một giao thức khác ở các giai đoạn sau của quá trình phát triển ứng dụng.

- Một cách khác để phân loại các ứng dụng khách là tùy thuộc vào việc ứng dụng khách là đồng bộ hay không đồng bộ. Ứng dụng khách đồng bộ sử dụng lệnh gọi API socket đồng bộ chặn luồng thực thi cho đến khi hoàn thành hoạt động được yêu cầu hoặc xảy ra lỗi. Do đó, một ứng dụng khách TCP đồng bộ điển hình sẽ sử dụng phương thức `asio::ip::tcp::socket::write_some()` hoặc hàm `asio::write()` để gửi yêu cầu đến máy chủ và sau đó sử dụng `asio::ip::tcp::socket::read_some()` hoặc hàm `asio::read()` để nhận phản hồi.

- Ứng dụng khách không đồng bộ trái ngược với ứng dụng đồng bộ sử dụng lệnh gọi API **socket** không đồng bộ. Ví dụ: một máy khách TCP không đồng bộ có thể sử dụng phương thức `asio::ip::tcp::socket::async_write_some()` hoặc hàm `asio::async_write()` để gửi yêu cầu đến máy chủ và sau đó sử dụng `asio::ip::tcp::socket::async_read_some()` hoặc hàm `asio::async_read()` để nhận phản hồi không đồng bộ.

- Vì cấu trúc của máy khách đồng bộ khác biệt đáng kể so với cấu trúc của máy khách không đồng bộ, nên quyết định áp dụng phương pháp tiếp cận nào cần được đưa ra sớm ở giai đoạn thiết kế ứng dụng và quyết định này phải dựa trên việc phân tích cẩn thận các yêu cầu của ứng dụng. Bên cạnh đó, các con đường phát triển ứng dụng có thể xảy ra và các yêu cầu mới có thể xuất hiện trong tương lai cần được xem xét và tính đến.

### Synchronous versus asynchronous

- Thông thường, mỗi cách tiếp cận đều có ưu điểm và nhược điểm. Khi cách tiếp cận đồng bộ cho kết quả tốt hơn trong một tình huống, thì nó có thể hoàn toàn không được chấp nhận trong một tình huống khác. Trong trường hợp sau, nên sử dụng cách tiếp cận không đồng bộ. Hãy so sánh hai cách tiếp cận để hiểu rõ hơn khi nào sử dụng mỗi cách sẽ có lợi hơn.

- Ưu điểm chính của cách tiếp cận đồng bộ là tính đơn giản của nó. Máy khách đồng bộ dễ phát triển, gỡ lỗi và hỗ trợ hơn đáng kể so với máy khách không đồng bộ ngang bằng về mặt chức năng. Máy khách không đồng bộ phức tạp hơn do thực tế là các hoạt động không đồng bộ được chúng sử dụng hoàn thành ở những nơi khác trong code (chủ yếu là trong lệnh **callback**) so với chúng được khởi tạo. Thông thường, điều này yêu cầu phân bổ cấu trúc dữ liệu bổ sung trong bộ nhớ trống để giữ ngữ cảnh của các hàm yêu cầu và **callback**, đồng thời liên quan đến đồng bộ hóa luồng và các tính năng bổ sung khác có thể làm cho cấu trúc ứng dụng khá phức tạp và dễ xảy ra lỗi. Hầu hết các tính năng bổ sung này không được yêu cầu trong các máy khách đồng bộ. Bên cạnh đó, cách tiếp cận không đồng bộ mang lại chi phí tính toán và bộ nhớ bổ sung, làm cho nó kém hiệu quả hơn so với cách tiếp cận đồng bộ trong một số điều kiện.

- Tuy nhiên, cách tiếp cận đồng bộ có một số hạn chế về chức năng, điều này thường làm cho cách tiếp cận này không được chấp nhận. Những hạn chế này bao gồm việc không thể hủy một hoạt động đồng bộ sau khi nó đã bắt đầu, hoặc ấn định thời gian chờ để nó bị gián đoạn nếu nó đang chạy lâu hơn một khoảng thời gian nhất định. Trái ngược với các hoạt động đồng bộ, các hoạt động không đồng bộ có thể bị hủy bất kỳ lúc nào sau khi bắt đầu hoạt động và trước thời điểm nó hoàn thành.

- Hãy tưởng tượng một trình duyệt web hiện đại điển hình. Hủy yêu cầu là một tính năng rất quan trọng của một ứng dụng khách thuộc loại này. Sau khi ra lệnh để tải một trang web cụ thể, người dùng có thể thay đổi ý định và quyết định hủy lệnh trước khi trang được tải. Từ quan điểm của người dùng, sẽ khá lạ nếu không thể hủy lệnh cho đến khi trang được tải đầy đủ. Do đó, đây là khi một cách tiếp cận đồng bộ không phải là một lựa chọn tốt.

- Bên cạnh sự khác biệt về độ phức tạp và chức năng được mô tả ở trên, hai cách tiếp cận còn khác nhau về hiệu quả khi chạy một số yêu cầu song song. trích xuất một số thông tin thú vị. Đưa ra một tệp có danh sách dài các trang web (ví dụ hàng triệu), ứng dụng phải duyệt qua tất cả các trang của từng trang được liệt kê trong tệp và sau đó xử lý từng trang. Đương nhiên, một trong những yêu cầu quan trọng của ứng dụng là thực hiện tác vụ càng nhanh càng tốt. Với những yêu cầu này, chúng ta nên chọn cách tiếp cận nào, đồng bộ hay không đồng bộ?

- Trước khi trả lời câu hỏi này, chúng ta hãy xem xét các giai đoạn của vòng đời yêu cầu và thời gian của chúng từ quan điểm của ứng dụng khách. Về mặt khái niệm, vòng đời yêu cầu bao gồm năm giai đoạn như sau:

    - Chuẩn bị yêu cầu: Giai đoạn này liên quan đến bất kỳ thao tác nào cần thiết để chuẩn bị thông báo yêu cầu. Thời gian của bước này phụ thuộc vào vấn đề cụ thể mà ứng dụng giải quyết. Trong ví dụ của chúng tôi, điều này có thể là đọc địa chỉ trang web tiếp theo từ tệp đầu vào và xây dựng một chuỗi đại diện cho một yêu cầu theo giao thức HTTP.

    - Truyền yêu cầu từ máy khách đến máy chủ: Giai đoạn này giả định việc truyền dữ liệu yêu cầu từ máy khách đến máy chủ qua mạng. Thời gian của bước này không phụ thuộc vào ứng dụng khách. Nó phụ thuộc vào các thuộc tính và trạng thái hiện tại của mạng.

    - Xử lý yêu cầu của máy chủ: Thời gian của bước này phụ thuộc vào thuộc tính của máy chủ và tải hiện tại của nó. Trong ví dụ của chúng tôi, ứng dụng máy chủ là một máy chủ web và việc xử lý yêu cầu nằm trong việc xây dựng một trang web được yêu cầu, có thể liên quan đến các hoạt động I/O như đọc tệp và tải dữ liệu từ cơ sở dữ liệu.

    - Truyền phản hồi từ máy chủ đến máy khách: Giống như giai đoạn 2, giai đoạn này cũng giả định việc truyền dữ liệu qua mạng; tuy nhiên, lần này nó theo hướng ngược lại - từ máy chủ đến máy khách. Thời gian của giai đoạn này không phụ thuộc vào máy khách hoặc máy chủ. Nó chỉ phụ thuộc vào các thuộc tính và trạng thái của mạng.

    - Xử lý phản hồi của ứng dụng khách: Thời gian của giai đoạn này phụ thuộc vào một tác vụ cụ thể mà ứng dụng khách dự định thực hiện. Trong ví dụ của chúng tôi, điều này có thể là quét trang web, trích xuất thông tin thú vị và lưu trữ nó vào cơ sở dữ liệu.

- Lưu ý rằng, để đơn giản, chúng tôi đã bỏ qua các phần phụ cấp thấp như thiết lập kết nối và tắt kết nối, những điều này rất quan trọng khi sử dụng giao thức TCP nhưng không thêm giá trị đáng kể trong mô hình khái niệm của chúng tôi về vòng đời yêu cầu.

- Như chúng ta thấy, chỉ trong giai đoạn 1 và 5, khách hàng mới thực hiện một số công việc hiệu quả liên quan đến yêu cầu. Sau khi bắt đầu truyền dữ liệu yêu cầu ở cuối giai đoạn 1, khách hàng phải đợi trong ba giai đoạn tiếp theo (2, 3 và 4) của vòng đời yêu cầu trước khi nó có thể nhận được phản hồi và xử lý.

- Bây giờ, với các giai đoạn của vòng đời yêu cầu, hãy xem điều gì sẽ xảy ra khi chúng tôi áp dụng các phương pháp tiếp cận đồng bộ và không đồng bộ để triển khai trình thu thập thông tin web mẫu của mình.

- Nếu chúng tôi áp dụng phương pháp đồng bộ, chuỗi thực thi xử lý đồng bộ một yêu cầu duy nhất sẽ ở trạng thái ngủ trong giai đoạn 2-4 của vòng đời yêu cầu và chỉ trong giai đoạn 1 và 5, nó mới thực hiện một công việc hiệu quả (để đơn giản, chúng tôi giả sử rằng giai đoạn 1 và 5 không bao gồm các hướng dẫn chặn luồng). Điều này có nghĩa là tài nguyên của một hệ điều hành, cụ thể là một luồng, được sử dụng không hiệu quả, bởi vì đôi khi nó chỉ đơn giản là không làm gì trong khi vẫn còn rất nhiều công việc - hàng triệu trang khác để yêu cầu và xử lý. Trong tình huống này, cách tiếp cận không đồng bộ có vẻ hiệu quả hơn. Với cách tiếp cận không đồng bộ, thay vì một luồng bị chặn trong các giai đoạn 2-4 của vòng đời yêu cầu, nó có thể được sử dụng hiệu quả để thực hiện các giai đoạn 1 hoặc 5 của một yêu cầu khác.

- Do đó, chúng tôi chỉ đạo một luồng xử lý các giai đoạn khác nhau của các yêu cầu khác nhau (điều này được gọi là chồng chéo), dẫn đến việc sử dụng hiệu quả hơn một luồng và do đó tăng hiệu suất tổng thể của ứng dụng.

- Tuy nhiên, cách tiếp cận không đồng bộ không phải lúc nào cũng hiệu quả hơn cách tiếp cận đồng bộ. Như đã được đề cập, hoạt động không đồng bộ bao hàm tổng chi phí tính toán bổ sung, có nghĩa là thời lượng tổng thể của hoạt động không đồng bộ (từ khi bắt đầu cho đến khi hoàn thành) lớn hơn một chút so với hoạt động đồng bộ tương đương. Điều này có nghĩa là, nếu tổng thời lượng trung bình của các giai đoạn 2-4 nhỏ hơn tổng thời lượng của phương pháp tiếp cận không đồng bộ về thời gian cho mỗi yêu cầu đơn lẻ, thì phương pháp tiếp cận đồng bộ sẽ hiệu quả hơn và do đó có thể được coi là cách phù hợp để đi.

Đá- nh giá tổng thời lượng của các giai đoạn 2-4 của vòng đời yêu cầu và chi phí của phương pháp tiếp cận không đồng bộ thường được thực hiện bằng thực nghiệm. Thời lượng có thể thay đổi đáng kể và nó phụ thuộc vào các thuộc tính và trạng thái của mạng mà các yêu cầu và phản hồi được truyền qua đó cũng như các thuộc tính và mức tải của ứng dụng máy chủ phục vụ yêu cầu.

### The sample protocol

- Trong chương này, chúng ta sẽ xem xét ba code, mỗi code trình bày cách triển khai một loại ứng dụng khách cụ thể: ứng dụng khách UDP đồng bộ, ứng dụng TCP đồng bộ và ứng dụng khách TCP không đồng bộ. Trong tất cả các code, giả định rằng ứng dụng khách giao tiếp với ứng dụng máy chủ bằng giao thức cấp ứng dụng đơn giản sau đây.

- Ứng dụng máy chủ chấp nhận một yêu cầu được biểu diễn dưới dạng chuỗi ASCII. Chuỗi có định dạng sau:

```cpp
EMULATE_LONG_COMP_OP [s]<LF>
```

- Trong đó `[s]` là một giá trị nguyên dương và `<LF>` là ASCII là một ký hiệu dòng mới. Máy chủ diễn giải chuỗi này như một yêu cầu thực hiện một hoạt động giả kéo dài trong `[s]` giây. Ví dụ, một chuỗi yêu cầu có thể trông như sau:

```cpp
"EMULATE_LONG_COMP_OP 10\n"
```

- Điều này có nghĩa là máy khách gửi yêu cầu này muốn máy chủ thực hiện hoạt động giả trong 10 giây và sau đó gửi phản hồi cho nó.

- Giống như yêu cầu, phản hồi do máy chủ trả về được biểu thị bằng một chuỗi ASCII. Có thể `OK<LF>` nếu thao tác hoàn thành thành công hoặc `ERROR<LF>` nếu thao tác không thành công.

---

## Implementing a synchronous TCP client

- Máy khách TCP đồng bộ là một phần của ứng dụng phân tán tuân thủ các câu lệnh sau:

    - Hoạt động như một máy khách trong mô hình giao tiếp máy khách-máy chủ

    - Giao tiếp với ứng dụng máy chủ bằng giao thức TCP

    - Sử dụng các hoạt động I/O và điều khiển (ít nhất là các hoạt động I / O liên quan đến giao tiếp với máy chủ) để chặn luồng thực thi cho đến khi hoạt động tương ứng hoàn thành hoặc xảy ra lỗi.

- Một ứng dụng khách TCP đồng bộ điển hình hoạt động theo thuật toán sau:

    - Lấy địa chỉ IP và số cổng giao thức của ứng dụng máy chủ.

    - Allocate một **socket** hoạt động.

    - Thiết lập kết nối với ứng dụng máy chủ.

    - Trao đổi tin nhắn với máy chủ.

    - Ngắt kết nối.

    - Deallocate **socket**.

Công thức này trình bày cách triển khai ứng dụng khách TCP đồng bộ với Boost.Asio.

[**CODE**](asio-example/chapter-3/SyncTCPClient.cpp) - code mẫu triển khai ứng dụng khách TCP đồng bộ với `Boost.Asio`.

---

## Implementing a synchronous UDP client

- Máy khách UDP đồng bộ là một phần của ứng dụng phân tán tuân thủ các câu lệnh sau:

    - Hoạt động như một máy khách trong mô hình giao tiếp máy khách-máy chủ

    - Giao tiếp với ứng dụng máy chủ bằng giao thức UDP

    - Sử dụng các hoạt động I / O và điều khiển (ít nhất là các hoạt động I / O liên quan đến giao tiếp với máy chủ) chặn luồng thực thi cho đến khi hoạt động tương ứng hoàn thành hoặc xảy ra lỗi

- Một máy khách UDP đồng bộ điển hình hoạt động theo thuật toán sau:

    - Lấy địa chỉ IP và số cổng giao thức của mỗi máy chủ mà ứng dụng khách dự định giao tiếp.

    - Allocate một **socket** UDP.

    - Trao đổi tin nhắn với các máy chủ.

    - Deallocate **socket**.

[**CODE**](asio-example/chapter-3/SyncUDPClient.cpp) - code mẫu cách triển khai ứng dụng khách UDP đồng bộ với Boost.Asio.

---

## Implementing an asynchronous TCP client

- Như nó đã được đề cập trong phần giới thiệu của chương này, máy khách không đồng bộ đơn giản nhất có cấu trúc phức tạp hơn máy khách đồng bộ tương đương. Khi chúng tôi thêm một tính năng như hủy yêu cầu vào máy khách không đồng bộ, nó thậm chí còn trở nên phức tạp hơn.

- Trong công thức này, chúng ta sẽ xem xét một ứng dụng khách TCP không đồng bộ hỗ trợ thực thi không đồng bộ các yêu cầu và chức năng hủy yêu cầu. Dưới đây là danh sách các yêu cầu mà ứng dụng sẽ đáp ứng:

     - Đầu vào từ người dùng phải được xử lý trong một chuỗi riêng biệt - chuỗi giao diện người dùng. Chủ đề này sẽ không bao giờ bị chặn trong một khoảng thời gian đáng chú ý.

     - Người dùng có thể đưa ra nhiều yêu cầu đến các máy chủ khác nhau.

     - Người dùng có thể đưa ra một yêu cầu mới trước khi các yêu cầu đã phát hành trước đó hoàn tất.

     - Người dùng sẽ có thể hủy các yêu cầu đã đưa ra trước đó trước khi chúng hoàn tất.
